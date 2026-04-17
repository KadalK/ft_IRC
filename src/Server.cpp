#include "Server.hpp"

Server::Server() : _port(-1), _serverFd(-1) {}
Server::Server(int port) : _port(port), _serverFd(-1) {}

//Exception
const char* Server::NoClient::what() const throw(){
	return("Client not found");
}


void	Server::start(){
	for (;;)
	{

	}
}

//Getter
int Server::getServerFd() const{
	return(this->_serverFd);
}

Client*	Server::getClient(int fd) const{
	std::map<int, Client*>::const_iterator it = _clients.find(fd);

	if (it != _clients.end())
		return it->second;

	return NULL;
}

void	Server::addClient(Client* client){
	if (!client)
		throw NoClient();
	this->_clients[this->getServerFd()] = client;
}

void	Server::removeClient(int fd){
	std::map<int, Client*>::iterator it = _clients.find(fd);

	if (it == _clients.end())
		return;
	delete it->second;
	_clients.erase(it);
}


void	Server::handleJoin(Client* client, const std::string& channelName){}

void	Server::removeClientFromAllChannels(Client* client){
	if (!client)
		throw NoClient();
	const std::map<std::string, Channel*>& channels = _channels.getAllChannels();

	for (std::map<std::string, Channel*>::const_iterator it = channels.begin();	it != channels.end(); ++it)
	{
		if (it->second)
			it->second->removeClient(client);
	}
}


Server::~Server(){}