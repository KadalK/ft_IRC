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
#include "CommandsHandler.hpp"
#include "ClientHandler.hpp"
#include "ChannelHandler.hpp"
#include <arpa/inet.h>

extern bool g_isRunning;

class Server{

	private:
		int _port;
		int _serverSocketFd;
		int _epollFd;

		std::vector<epoll_event> _events;
		std::string _password;

		ChannelHandler _channelHandler;
		ClientHandler _clientHandler;
    CommandsHandler _commandsHandler;

	public:
		Server(int port, std::string password);
		// Server(const Server& copy);
		// Server& operator=(const Server& other);
		// Server& operator=(const Server& other);
		void init();
		void run();
		void connectNewClient();
		void disconnectClient(int fd);
		void eventToServer(int fd);
		void setEpollOut(const std::vector<int>& vec);
		void eventToClient(int fd);

	~Server();
};

#endif
