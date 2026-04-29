#include "commands/Pass.hpp"
#include <iostream>

// TODO:
//   replies
// ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

Pass::Pass(std::string passServ): _passServ(passServ) {}

void Pass::execute(Client& client, ClientHandler &, ChannelHandler &, const std::vector<std::string>& arg)
{
	if (arg.size() < 1)
	{
		std::cout << "[debug]: invalid format" << std::endl;
		client.appendBufferOut("invalid format");
		return;
	}

	const std::string& pass = arg[0];

	if (client.getPassBool())
	{
		std::cout << "[debug]: already registered" << std::endl;
		client.appendBufferOut("already registered");
		return;
	}

	if (pass != this->_passServ)
	{
		std::cout << "[debug]: invalid password" << std::endl;
		client.appendBufferOut("invalid password");
		return;
	}

  client.setPassBool(true);
}

Pass::~Pass(){}
