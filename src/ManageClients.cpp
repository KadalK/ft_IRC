#include "ManageClients.hpp"

ManageClient::ManageClient(){}

Client* ManageClient::createClient(int fd){
	Client* client = new Client(fd);
	_clients[fd] = client;
	return client;
}

void ManageClient::deleteClient(int fd){
	
}

Client* ManageClient::getClient(int fd){
	return (this->_clients[fd]);
}

ManageClient::~ManageClient(){}