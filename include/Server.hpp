#pragma once


#include <iostream>
#include "Client.hpp"
#include "ManageChannel.hpp"

class Server{
private:
	int	_port;
	int	_serverFd;

	std::map<int, Client*> _clients;
	ManageChannel _channels;
	Server& operator=(const Server& other);
	Server(const Server& copy);
public:
	Server();
	Server(int port);

	//Exception
	class NoClient : public std::exception{
		virtual const char* what() const throw();
	};

	//Getter
	Client*	getClient(int fd) const;
	int		getServerFd() const;

	void	start();

	void	addClient(Client* client);
	void	removeClient(int fd);

	void	handleJoin(Client* client, const std::string& channelName);
	void	removeClientFromAllChannels(Client* client);


	~Server();
};
