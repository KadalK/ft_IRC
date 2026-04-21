#include "Server.hpp"

Server::Server(int port,std::string password) : _port(port) , _password(password){}

void Server::init()
{
	int optval = 1;
	this->_serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(this->_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(this->_port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	bind(this->_serverSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	fcntl(this->_serverSocketFd, F_SETFL, O_NONBLOCK);
	listen(this->_serverSocketFd, 5);
}

std::string Server::getPass(){
	return(this->_password);
}


void Server::createNewClient()
{
	int clientSocketFd = accept(this->_serverSocketFd, NULL, NULL);
	epoll_event clientEvent;
	Client Client;
	Client.setFd(clientSocketFd);
	this->_registry[clientSocketFd] = Client;
	clientEvent.events = EPOLLIN;
	clientEvent.data.fd = clientSocketFd;
	fcntl(clientSocketFd, F_SETFL, O_NONBLOCK);
	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, clientSocketFd, &clientEvent);
	std::cout << "new CLIENT connected " << clientSocketFd << std::endl;
}

void Server::removeClient(int fd)
{
	epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, fd, NULL);
	this->_registry.erase(fd);
	close(fd);
	std::cout << "client remove + fd :" << fd << std::endl;
}


void Server::handleClientData(int fd)
{
	char temp[1024] = {0};
	int bytes = recv(fd, temp, sizeof(temp), 0);
	if (bytes <= 0)
		this->removeClient(fd);
	else
	{
		this->_registry[fd].appendBuffer(temp);
		size_t pos;
		while ((pos = this->_registry[fd].getBuffer().find("\r\n")) != std::string::npos)
		{
			std::string command = this->_registry[fd].getBuffer().substr(0, pos); //jaurai kiffer mettre le GetBuffer en ref const pour ne pas faire de copie et que ca soit plus secure
			this->_registry[fd].setBuffer(this->_registry[fd].getBuffer().erase(0, pos + 2));
			// envoie au parseur.
			std::cout << "commande recu :" << command << " fd :" << fd  << "lenght : "<< command.length() << std::endl;
		}
	}
}

void Server::run(){
	this->_epollFd = epoll_create1(0);
	epoll_event eventsServer;
	eventsServer.events = EPOLLIN;
	eventsServer.data.fd = this->_serverSocketFd;
	this->_events.resize(64);
	epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, eventsServer.data.fd, &eventsServer);

	while (true)
	{
		int eventCount = epoll_wait(this->_epollFd, this->_events.data(), 64, -1);
		for (int i = 0; i < eventCount; i++)
		{
			int clientSocketFd = this->_events[i].data.fd;
			if (clientSocketFd == this->_serverSocketFd)
				this->createNewClient();
			else
				this->handleClientData(clientSocketFd);
		}
	}
}


// void Server::broadcast(const std::string &msg)
// {
// 	(void)msg;
// 	std::cout << "fontion broadcast Serveur";
// }

Server::~Server() {}
