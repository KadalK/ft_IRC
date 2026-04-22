#include "Server.hpp"
#include "SystemException.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password)
{
}

void Server::init()
{
	int optval = 1;
	this->_serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocketFd < 0)
		throw SystemException("Erreur de création du socket");
	if (setsockopt(this->_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		throw SystemException("Erreur de configuration du socket");
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(this->_port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	if (bind(this->_serverSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
		throw SystemException("Erreur d'attachement au port");
	if (fcntl(this->_serverSocketFd, F_SETFL, O_NONBLOCK) < 0)
		throw SystemException("Erreur lors du passage en mode non-bloquant");
	if (listen(this->_serverSocketFd, 5) < 0)
		throw SystemException("Impossible d'ouvrir les portes du serveur pour écouter");
}

void Server::createNewClient()
{
	int clientSocketFd = accept(this->_serverSocketFd, NULL, NULL);
	epoll_event clientEvent;
	Client *newCLient = new Client;
	newCLient->setFd(clientSocketFd);
	this->_registry[clientSocketFd] = newCLient;
	clientEvent.events = EPOLLIN;
	clientEvent.data.fd = clientSocketFd;
	fcntl(clientSocketFd, F_SETFL, O_NONBLOCK);
	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, clientSocketFd, &clientEvent);
	std::cout << "new CLIENT connected " << clientSocketFd << std::endl;
}

void Server::removeClient(int fd)
{
	epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, fd, NULL);
	Client *toDelete = this->_registry[fd];
	delete toDelete;
	this->_registry.erase(fd);
	close(fd);
	std::cout << "client remove " << this->_registry[fd]->getNickname() << " le fd etait : " << fd << std::endl;
}

void Server::handleClientData(int fd)
{
	char temp[1024] = {0};
	int bytes = recv(fd, temp, sizeof(temp), 0);
	if (bytes <= 0)
		this->removeClient(fd);
	else
	{
		this->_registry[fd]->appendBuffer(temp);
		size_t pos;
		while ((pos = this->_registry[fd]->getBuffer().find("\r\n")) != std::string::npos)
		{
			std::string command = this->_registry[fd]->getBuffer().substr(0, pos);
			this->_registry[fd]->setBuffer(this->_registry[fd]->getBuffer().erase(0, pos + 2));
			// envoie au parseur.
			std::cout << "commande recu :" << command << " fd :" << fd << "lenght : " << command.length() << std::endl;
		}
	}
}

void Server::sendToClient(int fd)
{
	if (this->_registry.find(fd) == this->_registry.end())
		return;
	Client *client = this->_registry[fd];
	std::string message = client->getBufferOut();
	if (message.empty())
		return;
	int bytesSent = send(fd, message.c_str(), message.length(), MSG_NOSIGNAL);
	if (!bytesSent)
	{
		this->removeClient(fd);
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

Client *Server::getClientByNickname(std::string nickname)
{
	std::map<int, Client *>::iterator it = this->_registry.begin();
	while (it != this->_registry.end())
	{
		if (it->second->getNickname() == nickname)
			return (it->second);
		it++;
	}
	return NULL;
}

void Server::clientWrite(int fd)
{
	epoll_event event;
	event.events = EPOLLIN | EPOLLOUT;
	event.data.fd = fd;
	epoll_ctl(this->_epollFd, EPOLL_CTL_MOD, fd, &event);
}

void Server::run()
{
	this->_epollFd = epoll_create1(0);
	epoll_event eventsServer;
	eventsServer.events = EPOLLIN;
	eventsServer.data.fd = this->_serverSocketFd;
	this->_events.resize(64);
	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, eventsServer.data.fd, &eventsServer);

	while (g_isRunning)
	{
		int eventCount = epoll_wait(this->_epollFd, this->_events.data(), 64, -1);
		for (int i = 0; i < eventCount; i++)
		{
			int clientSocketFd = this->_events[i].data.fd;
			u_int32_t flags = this->_events[i].events;
			if (clientSocketFd == this->_serverSocketFd)
				this->createNewClient();
			else
			{
				if (flags & EPOLLIN)
					this->handleClientData(clientSocketFd);
				if (flags & EPOLLOUT)
					this->sendToClient(clientSocketFd);
			}
		}
	}
}

Server::~Server()
{
	std::map<int, Client *>::iterator it = this->_registry.begin();
	while (it != this->_registry.end())
	{
		delete it->second;
		close(it->first);
	}
	if (this->_serverSocketFd != -1)
		close(this->_serverSocketFd);
	if (this->_epollFd != -1)
		close(this->_epollFd);
}
