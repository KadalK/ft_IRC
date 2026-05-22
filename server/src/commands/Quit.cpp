#include "commands/Quit.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <iostream>
#include "ClientHandler.hpp"


Quit::Quit(){}


void Quit::execute(Client &sender, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string> &arg){

	std::string msg = "";

	if (arg.size() > 2)
	{
		msg = arg[1];
	}


	std::map<int, Client *> clients = clH.getRegistery();
	std::map<std::string, Channel *> listChan = chH.getChannelList();


	for (std::map<int, Client *>::iterator itAC = clients.begin();
			   itAC != clients.end(); itAC++)
	{
		for (std::map<std::string, Channel *>::iterator itACh = listChan.begin(); itACh != listChan.end(); ++itACh)
		{
			if (itACh->second->isClientInChannel(sender) == true)
			{
				if (itACh->second->isClientInChannel(*itAC->second) == true)
				{
					itAC->second->appendBufferOut(sender.getNickname() + " QUIT :" + msg + "\r\n");
				}
			}
		}
	}
	std::cout << "[DEBUG]:  " << sender.getToDisconnect() << std::endl;
	sender.setToDisconnect(true);
}

Quit::~Quit() {}