#include "Pass.hpp"
#include <iostream>

// TODO:
//   replies
// ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

Pass::Pass(std::string passServ): _passServ(passServ) {}

void Pass::execute(Client& client, ClientHandler &, ChannelHandler &, const std::vector<std::string>& arg)
{
	if (arg.size() < 2)
	{
		std::cout << "[debug]: invalid format" << std::endl;
		client.setBufferOut("invalid format");
		return;
	}

	const std::string& pass = arg[1];

	if (client.isRegistered())
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

	client.setAuth(true);
}

Pass::~Pass(){}
// void pass::execute(client& client, const std::vector<std::string>& arg,  std::string& passserv){
// 	if (arg.size() < 2)
// 	{
// 		std::cout << "[debug]: invalid format" << std::endl;
// 		client.setbufferout("invalid format");
// 		return;
// 	}
//
// 	const std::string& pass = arg[1];
//
// 	if (client.isregistered())
// 	{
// 		std::cout << "[debug]: already registered" << std::endl;
// 		client.setbufferout("already registered");
// 		return;
// 	}
//
// 	if (pass != passserv)
// 	{
// 		std::cout << "[debug]: invalid password" << std::endl;
// 		client.setbufferout("invalid password");
// 		return;
// 	}
//
// 	client.setauth(true);
// }
