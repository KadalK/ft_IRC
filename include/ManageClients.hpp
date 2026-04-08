#ifndef MANAGECLIENT_HPP
#define MANAGECLIENT_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include "Client.hpp"

class ManageClient {
private:
	std::map<int, Client*> _clients; // fd -> Client

	ManageClient(const ManageClient&);
	ManageClient& operator=(const ManageClient&);

public:
	ManageClient();

	Client* createClient(int fd);
	void deleteClient(int fd);

	Client* getClient(int fd);

	~ManageClient();
};

#endif