#include "commands/Away.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

#include "iostream"

Away::Away() {}


void Away::execute(Client &sender, ClientHandler &, ChannelHandler &, const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    sender.setAwayBool(false);
    sender.appendBufferOut(Replies::RPL_UNAWAY(sender.getNickname()));
  }
  else if (arg.size() >= 1)
  {
    std::cout << "ARG 1 ou plus " << std::endl;
    sender.setAwayBool(true);
    sender.setAwayMsg(arg[0]);
    sender.appendBufferOut(Replies::RPL_NOWAWAY(sender.getNickname()));
  }
  return;
}

Away::~Away() {}
