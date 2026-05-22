#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "SystemException.hpp"
#include <iostream>

Server::Server(int port, std::string password)
    : _port(port), _serverSocketFd(-1), _epollFd(-1), _password(password),
      _channelHandler(), _clientHandler(),
      _commandsHandler(_clientHandler, _channelHandler, _password)
{
}

void Server::init()
{
  int optval = 1;
  this->_serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_serverSocketFd < 0)
    throw SystemException("Error during the creation of the socket");
  if (setsockopt(this->_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &optval,
                 sizeof(optval)) < 0)
    throw SystemException("Error during the configuration of the socket");
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(this->_port);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->_serverSocketFd, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) < 0)
    throw SystemException("Error during the bind of the port");
  if (fcntl(this->_serverSocketFd, F_SETFL, O_NONBLOCK) < 0)
    throw SystemException("Error from the fcntl function");
  if (listen(this->_serverSocketFd, 5) < 0)
    throw SystemException("Error can't be able to listen");
}

void Server::connectNewClient()
{
  struct sockaddr_in clientAddress;
  socklen_t AddressLen = sizeof(clientAddress);
  int clientSocketFd = accept(this->_serverSocketFd,
                              (struct sockaddr *)&clientAddress, &AddressLen);
  if (clientSocketFd < 0)
  {
    std::cout << "Error: accept" << std::endl;
    return;
  }
  char *ipString = inet_ntoa(clientAddress.sin_addr);
  std::string hostname = ipString;
  if (fcntl(clientSocketFd, F_SETFL, O_NONBLOCK) < 0)
  {
    std::cout << "Error: fcntl" << std::endl;
    close(clientSocketFd);
    return;
  }
  epoll_event clientEvent;
  clientEvent.events = EPOLLIN;
  clientEvent.data.fd = clientSocketFd;
  if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, clientSocketFd, &clientEvent) <
      0)
  {
    std::cout << "Error: epoll_ctl" << std::endl;
    close(clientSocketFd);
    return;
  }
  std::string time = this->_time;
  this->_clientHandler.addClient(clientSocketFd, hostname, time);
}

void Server::disconnectClient(int fd)
{
  this->_channelHandler.deleteClient(this->_clientHandler.getClientByFd(fd));
  this->_clientHandler.removeClient(fd);
  epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, fd, NULL);
  close(fd);
}

static void announcePart(Client &sender, ChannelHandler &chH)
{
  for (std::map<std::string, Channel *>::const_iterator it =
           chH.getChannelList().begin();
       it != chH.getChannelList().end(); ++it)
  {
    if (it->second->isClientInChannel(sender))
    {
      it->second->broadcast(
          Replies::BC_PART(sender.getFullName(), it->second->getName(), ""),
          &sender, false);
    }
  }
}

void Server::eventToServer(int fd)
{
  char temp[1024] = {0};
  int bytes = recv(fd, temp, sizeof(temp), 0);
  Client *client = this->_clientHandler.getClientByFd(fd);
  if (bytes <= 0)
  {
    announcePart(*client, this->_channelHandler);
    this->disconnectClient(fd);
  }
  else
  {
    std::string message(temp, bytes);
    client->appendBuffer(message);
    if (client->getBuffer().length() > 2048)
    {
      client->setBuffer("");
      client->appendBufferOut(":ircserv 417 " + client->getNickname() +
                              " :Line too long\r\n");
      return;
    }
    size_t pos;
    while ((pos = client->getBuffer().find("\r\n")) != std::string::npos)
    {
      std::string command = client->getBuffer().substr(0, pos);
      client->setBuffer(client->getBuffer().erase(0, pos + 2));
      this->_commandsHandler.processCommand(*client, this->_clientHandler,
                                            this->_channelHandler, command);
      std::cout
          << "received command : [" << command << "]" << std::endl
          << "sender's fd      : [" << fd << "]" << std::endl
          << "lenght           : [" << command.length() << "]" << std::endl
          << "------------------------------------------------------------"
          << std::endl;
    }
  }
}

void Server::eventToClient(int fd)
{
  if (this->_clientHandler.getClientByFd(fd) == NULL)
    return;
  Client *client = this->_clientHandler.getClientByFd(fd);
  std::string message = client->getBufferOut();
  if (message.empty())
    return;
  int bytesSent = send(fd, message.c_str(), message.length(), MSG_NOSIGNAL);
  if (bytesSent <= 0)
  {
    this->disconnectClient(fd);
    return;
  }
  client->setBufferOut(message.erase(0, bytesSent));
  if (client->getBufferOut().empty())
  {
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;
    epoll_ctl(this->_epollFd, EPOLL_CTL_MOD, fd, &event);
  }
}

void Server::setEpollOut(const std::vector<int> &vec)
{
  for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
  {
    epoll_event event;
    event.events = EPOLLIN | EPOLLOUT;
    event.data.fd = *it;
    epoll_ctl(this->_epollFd, EPOLL_CTL_MOD, *it, &event);
  }
}

void Server::run()
{
  this->_epollFd = epoll_create1(0);
  epoll_event eventsServer;
  eventsServer.events = EPOLLIN;
  eventsServer.data.fd = this->_serverSocketFd;
  this->_events.resize(64);
  epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, eventsServer.data.fd, &eventsServer);
  time_t rawtimes;
  time(&rawtimes);
  this->_time = ctime(&rawtimes);
  this->_time = this->_time.erase(this->_time.length() - 1);
  while (g_isRunning)
  {
    int eventCount = epoll_wait(this->_epollFd, this->_events.data(), 64, -1);
    for (int i = 0; i < eventCount; i++)
    {
      int clientSocketFd = this->_events[i].data.fd;
      u_int32_t flags = this->_events[i].events;
      if (clientSocketFd == this->_serverSocketFd)
        this->connectNewClient();
      else
      {
        if (flags & EPOLLIN)
          this->eventToServer(clientSocketFd);
        if (flags & EPOLLOUT)
          this->eventToClient(clientSocketFd);
        Client* client = this->_clientHandler.getClientByFd(clientSocketFd);
        if (client != NULL && client->getToDisconnect() == true)
          this->disconnectClient(clientSocketFd);
      }
    }
    std::vector<int> vec = this->_clientHandler.getFdWithData();
    if (!vec.empty())
      setEpollOut(vec);
  }
}

Server::~Server()
{
  std::vector<int> vec = this->_clientHandler.getAllFd();
  for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    close(*it);
  if (this->_serverSocketFd != -1)
    close(this->_serverSocketFd);
  if (this->_epollFd != -1)
    close(this->_epollFd);
}
