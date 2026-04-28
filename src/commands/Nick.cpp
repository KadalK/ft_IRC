#include "commands/Nick.hpp"
#include <iostream>

Nick::Nick(){}

//TODO:
//   replies
//           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//			 ERR_NICKNAMEINUSE               ERR_NICKCOLLISION

static bool validNick(const std::string& nick)
{
	if (nick.empty())
		return false;

	if (!std::isalpha(static_cast<unsigned char>(nick[0])) && nick[0] != '_')
		return false;

	for (size_t i = 0; i < nick.size(); ++i)
	{
		if (!std::isalnum(static_cast<unsigned char>(nick[i])) && nick[i] != '_' && nick[i] != '-')
			return false;
	}
	return true;
}

void Nick::execute(Client& client, ClientHandler &clH, ChannelHandler &, const std::vector<std::string>& arg)
{
	if (arg.size() < 2)
	{
		std::cout << "[DEBUG] : ERR_NONICKNAMEGIVEN" << std::endl;
		return;
	}

	const std::string& nick = arg[1];

	if (!validNick(nick))
	{
		std::cout << "[DEBUG] : ERR_ERRONEUSNICKNAME" << std::endl;
		return;
	}

	Client* existing = clH.getClientByNickname(nick);

	if (existing && existing != &client)
	{
		std::cout << "[DEBUG] : ERR_NICKNAMEINUSE" << std::endl;
		return;
	}

	client.setNickname(nick);
	client.setNickBool(true);
}

Nick::~Nick(){}
