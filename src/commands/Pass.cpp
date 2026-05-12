#include "commands/Pass.hpp"
#include <iostream>

// TODO:
//   replies
// ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

<<<<<<< Updated upstream
Pass::Pass(std::string passServ) : _passServ(passServ) {}

void Pass::execute(Client &client, ClientHandler &, ChannelHandler &,
                   const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    std::cout << "[debug]: invalid format" << std::endl;
    client.appendBufferOut("invalid format");
    return;
  }

  const std::string &pass = arg[0];

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
  if (client.getUserBool() && client.getNickBool())
    client.setAuth(true);
  return;
}

Pass::~Pass() {}
=======
Pass::Pass(std::string passServ): _passServ(passServ) {}

void Pass::execute(Client& client, ClientHandler &, ChannelHandler &, const std::vector<std::string>& arg)
{
	if (arg.empty() ||  arg.size() < 2)
	{
		std::cout << "[debug]: invalid format" << std::endl;
		client.appendBufferOut("Invalid format");
		return;
	}

	const std::string& pass = arg[0];

	if (client.getPassBool())
	{
		std::cout << "[debug]: already registered" << std::endl;
		client.appendBufferOut("Already registered");
		return;
	}

	if (pass != this->_passServ)
	{
		std::cout << "[debug]: invalid password" << std::endl;
		client.appendBufferOut("Invalid password");
		return;
	}

  client.setPassBool(true);
}

Pass::~Pass(){}
>>>>>>> Stashed changes
