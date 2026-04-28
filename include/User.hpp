#ifndef USER_HPP
#define USER_HPP

#include "ChannelHandler.hpp"
#include "CommandsHandler.hpp"
#include "ClientHandler.hpp"
#include "Client.hpp"
#include "Commands.hpp"
#include <iostream>

class User : public Commands {
private:
	User& operator=(const User& other);
	User(const User& copy);
public:
	User();

	void execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg);

	~User();
};

#endif
