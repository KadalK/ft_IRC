#include "commands/Quit.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <iostream>
#include "ClientHandler.hpp"


Quit::Quit(){}


void Quit::execute(Client &sender, ClientHandler &, ChannelHandler &chH, const std::vector<std::string> &arg){

	std::string msg = "";

	if (arg.size() > 1)
	{
		msg = arg[2];
	}

	std::map<std::string, Channel *> chanList =  chH.getChannelList();

	for (std::map<std::string ,Channel *>::iterator it = chanList.begin(); it != chanList.end(); ++it)
	{
		if (it->second->isClientInChannel(sender) == true)
		{
			sender.setBufferOut(sender.getNickname() + " QUIT :" + msg);
		}
	}
}

Quit::~Quit(){

}