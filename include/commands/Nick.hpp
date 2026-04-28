#ifndef NICK_HPP
#define NICK_HPP

#include "ChannelHandler.hpp"
#include "CommandsHandler.hpp"
#include "ClientHandler.hpp"
#include "Client.hpp"
#include "Commands.hpp"
#include <iostream>

class Nick : public Commands {
private:
	Nick& operator=(const Nick& other);
	Nick(const Nick& copy);
public:
	Nick();

	void execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg);

	~Nick();
};

#endif
