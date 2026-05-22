#pragma once

#include "../Commands.hpp"
#include <vector>

class Client;
class Server;
class ClientHandler;
class ChannelHandler;

class Quit: public Commands
{
private:
	Quit& operator=(const Quit&other);
	Quit(const Quit&copy);

public:
	Quit();

	void execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
				 const std::vector<std::string> &arg);

	~Quit();
};