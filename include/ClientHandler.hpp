#ifndef CLIENTHANDLER_HPP
#define CLIENTHANDLER_HPP

#include "Client.hpp"
#include <map>
#include <vector>

class ClientHandler
{
private:
	std::map<int, Client *> _registry;

public:
	ClientHandler(/* args */);
	~ClientHandler();

	void addClient(int fd);
	void removeClient(int fd);

	Client *getClientByNickname(std::string nickname);
	std::vector<int> getAllFd();
	std::vector<int> getFdWithData();

	Client *getClientByFd(int fd);
};

#endif
