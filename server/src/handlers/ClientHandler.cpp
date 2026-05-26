#include "ClientHandler.hpp"
#include "Client.hpp"
#include <iostream>

ClientHandler::ClientHandler() {}

void ClientHandler::addClient(int fd, std::string hostname, std::string time)
{
  Client *newClient = new Client();
  newClient->setFd(fd);
  newClient->setHostname(hostname);
  newClient->setTimeServ(time);
  this->_registry[fd] = newClient;
  std::cout << "Client connected  : " << " [FD: " << fd << "]" << std::endl;
}

void ClientHandler::removeClient(int fd)
{
  std::string nick = this->_registry[fd]->getNickname();
  delete this->_registry[fd];
  this->_registry.erase(fd);
  std::cout << "Client deleted  : " << nick << " [FD: " << fd << "]"
            << std::endl;
}

Client *ClientHandler::getClientByNickname(std::string nickname)
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
std::vector<int> ClientHandler::getAllFd()
{
  std::vector<int> vec;
  if (this->_registry.empty() == true)
    return vec;
  std::map<int, Client *>::iterator it = this->_registry.begin();
  while (it != this->_registry.end())
  {
    vec.push_back(it->first);
    it++;
  }
  return vec;
}

std::map<int, Client *> ClientHandler::getRegistery()
{
  return (this->_registry);
}

std::vector<int> ClientHandler::getFdWithData()
{
  std::vector<int> vec;
  std::map<int, Client *>::iterator it = this->_registry.begin();
  while (it != this->_registry.end())
  {
    if (!it->second->getBufferOut().empty())
      vec.push_back(it->first);
    ++it;
  }
  return vec;
}

Client *ClientHandler::getClientByFd(int fd)
{
  if (this->_registry.find(fd) != this->_registry.end())
    return this->_registry[fd];
  return NULL;
}

ClientHandler::~ClientHandler()
{
  for (std::map<int, Client *>::iterator it = this->_registry.begin();
       it != this->_registry.end(); it++)
    delete it->second;
  this->_registry.clear();
}
