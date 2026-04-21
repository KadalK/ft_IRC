#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include <vector>
#include <map>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "Client.hpp"
#include "Channel.hpp"

class Server{
private:
	int _port;
	std::string _password;
	int _serverSocketFd;
	int _epollFd;
	std::vector<epoll_event> _events;
	std::map <int,Client> _registry;
	std::map <std::string,Channel> _channels;

public:
	Server(int port, std::string password);
	// Server(const Server& copy);
	// Server& operator=(const Server& other);

	void init();
	void run();
	void createNewClient();
	void removeClient(int fd);
	void handleClientData(int fd);
	std::string getPass();

	// void broadcast(const std::string& msg);
	~Server();
};

#endif

