#include "Pass.hpp"
#include <iostream>

void Pass::execute(Client& client, const std::vector<std::string>& arg,  std::string& passServ){
	if (arg.size() < 2)
	{
		std::cout << "[DEBUG]: Invalid format" << std::endl;
		client.setBufferOut("Invalid format");
		return;
	}

	const std::string& pass = arg[1];

	if (client.isRegistered())
	{
		std::cout << "[DEBUG]: Already registered" << std::endl;
		client.setBufferOut("Already registered");
		return;
	}

	if (pass != passServ)
	{
		std::cout << "[DEBUG]: invalid password" << std::endl;
		client.setBufferOut("invalid password");
		return;
	}

	client.setAuth(true);
}

Pass::~Pass(){}
