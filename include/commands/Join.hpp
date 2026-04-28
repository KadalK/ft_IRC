#pragma once

#include "ChannelHandler.hpp"
#include "CommandsHandler.hpp"
#include "ClientHandler.hpp"
#include "Commands.hpp"

class Join : public Commands {
private:
	Join& operator=(const Join& other);
	Join(const Join& copy);
public:
	Join();

	void execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg);

  ~Join();
};
