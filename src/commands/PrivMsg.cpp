#include "Commands.hpp"
#include "commands/PrivMsg.hpp"
#include <string>

#include "Client.hpp"

// PrivMsg::PrivMsg() {}
// PrivMsg::PrivMsg(PrivMsg const &src) { (void)src; }
// PrivMsg::~PrivMsg() {};
// PrivMsg &PrivMsg::operator=(PrivMsg const &rhs) { (void)rhs; }
//
// void PrivMsg::execute(Client*, std::vector<std::string>)
// {
//
//   if (this->parsingMessage(p, rawText) != 0)
//     return (-1);//throw exception plus tard quoi en gros + errorMessage()
//
// }
//
// void parsingNickNames(std::string ){}
//
// size_t PrivMsg::parsingMessage(std::string rawText)
// {
//   size_t pos = rawText.find(':');
//   parsingNickNames(rawText.substr(0, pos));
//   p.textMessage = rawText + pos;



PrivMsg::PrivMsg(){}


static std::vector<std::string> extractTokens(const std::string &str)
{
	std::vector<std::string> v;
	size_t start = 0;
	size_t pos;
	while ((pos = str.find(",", start)) != std::string::npos)
	{
		if (!str.substr(start, pos - start).empty())
			v.push_back(str.substr(start, pos - start));
		start = pos + 1;
	}
	if (!str.substr(start).empty())
		v.push_back(str.substr(start));
	return (v);
}

std::string formatMsg(const std::string& msg, const std::string& sender, const std::string& target){
	return (":" + sender + " PRIVMSG " + target + " :" + msg + "\r\n");
}

void PrivMsg::execute(Client& client,ClientHandler &clH,ChannelHandler &chH,const std::vector<std::string>& arg)
{
	if (arg.size() < 2)
		return;

	std::vector<std::string> targets = extractTokens(arg[0]);
	const std::string& msg = arg[1];

	for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		const std::string& target = *it;

		std::string formatted = formatMsg(msg, client.getNickname(), target);
		//pour les chan
		if (target[0] == '#')
		{

			Channel* chan = chH.getChannelByName(target);
			if (!chan)
			{
				client.appendBufferOut("No such channel\r\n");
				continue;
			}
			chan->broadcast(formatMsg(msg, client.getNickname(), *it), &client);
		}
		//pour les cli
		else
		{
			Client* receiver = clH.getClientByNickname(target);
			if (!receiver)
			{
				client.appendBufferOut("No such nick\r\n");
				continue;
			}
			if (!receiver->getAuth())
			{
				client.appendBufferOut("Not authenticated\r\n");
				continue;
			}
			receiver->appendBufferOut(formatMsg(msg, client.getNickname(), *it));
		}
	}
}

PrivMsg::~PrivMsg(){}
