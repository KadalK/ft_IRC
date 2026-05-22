#include "commands/Away.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

#include "iostream"

Away::Away() {}


void Away::execute(Client &sender, ClientHandler & clH, ChannelHandler &, const std::vector<std::string> &arg)
{
  std::map<int, Client *> clients = clH.getRegistery();
  if (arg.empty())
  {
    sender.setAwayBool(false);
    for (std::map<int, Client *>::iterator it = clients.begin();
         it != clients.end(); it++)
    {
      if (it->second == &sender)
        sender.appendBufferOut(Replies::RPL_UNAWAY(sender.getNickname()));
      else
        it->second->appendBufferOut( Replies::BC_UNAWAY(sender.getNickname()));
    }
  }
  else if (arg.size() >= 1)
  {
    std::cout << "ARG 1 ou plus " << std::endl;
    sender.setAwayBool(true);
    sender.setAwayMsg(arg[0]);
    for (std::map<int, Client *>::iterator it = clients.begin();
         it != clients.end(); it++)
    {
      if (it->second == &sender)
        sender.appendBufferOut(Replies::RPL_NOWAWAY(sender.getNickname()));
      else
        it->second->appendBufferOut( Replies::BC_NOWAWAY(sender.getNickname(), sender.getAwayMsg()));
    }
  }
  return;
}

Away::~Away() {}
