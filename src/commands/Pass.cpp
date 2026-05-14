#include "commands/Pass.hpp"
#include <iostream>

// TODO:
//   replies
// ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

Pass::Pass(std::string passServ) : _passServ(passServ) {}

void Pass::execute(Client &client, ClientHandler &, ChannelHandler &,
				   const std::vector<std::string> &arg)
{
	if (arg.empty())
	{
		client.appendBufferOut(Replies::ERR_NEEDMOREPARAMS(client.getNickname(), "PASS"));
		return;
	}

	const std::string &pass = arg[0];

	if (client.getPassBool())
	{
		client.appendBufferOut(Replies::ERR_ALREADYREGISTERED(client.getNickname()));
		return;
	}

	if (pass != this->_passServ)
	{
		client.appendBufferOut(Replies::ERR_PASSWDMISMATCH(client.getNickname()));
		return;
	}

	client.setPassBool(true);
	if (client.getUserBool() && client.getNickBool())
		client.setAuth(true);
	return;
}

Pass::~Pass() {}