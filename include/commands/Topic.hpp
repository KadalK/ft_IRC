#pragma once

#include "../include/Commands.hpp"
#include <vector>
#include <iostream>


class Client;
class ClientHandler;
class ChannelHandler;

class Topic : public Commands
{
private:
	Topic(Topic const &src);
	Topic &operator=(Topic const &rhs);
public:
	Topic();

	void parsingMessage(std::string rawText);
	void execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg);
	void errorMessage(size_t errorValue);
	~Topic();
};