#include "Pass.hpp"
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
		client.setBufferOut("invalid format");
		return;
	}

	const std::string& pass = arg[0];

	if (client.getPassBool())
	{
		std::cout << "[debug]: already registered" << std::endl;
		client.setBufferOut("already registered");
		return;
	}

	if (pass != this->_passServ)
	{
		std::cout << "[debug]: invalid password" << std::endl;
		client.setBufferOut("invalid password");
		return;
	}

  client.setPassBool(true);
}

Pass::~Pass(){}
