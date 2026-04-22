#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <map>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <csignal>
#include "Client.hpp"
#include "Channel.hpp"

extern bool g_isRunning;

class Server{

	private:

		int _port;
		int _serverSocketFd;
		int _epollFd;

		std::vector<epoll_event> _events;
		std::string _serverName;
		std::string _creationDate;
		std::string _password;
		// mange client
		std::map <int,Client*> _registry;
		ManageChannel &_ManageChannel;
		ManageClient &_ManageClient;
		// Parser _parser;

	public:
		Server(int port, std::string password);
		// Server(const Server& copy);
		// Server& operator=(const Server& other);

		void init();
		void run();
		void createNewClient();
		void removeClient(int fd);

		void eventToServer(int fd);

		//mange client
		void clientWrite(int fd);

		void eventToClient(int fd);
		Client* getClientByNickname(std::string);

	~Server();
};

#endif
