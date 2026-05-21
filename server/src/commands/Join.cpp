#include "commands/Join.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"
#include <iostream>

Join::Join() {}

void Join::execute(Client &sender, ClientHandler &, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  std::vector<std::string> channels;
  std::vector<std::string> passwords;
  std::vector<std::string>::iterator pIt;
  std::string inPassword;

  if (arg.empty())
    return (sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "JOIN")));
  channels = this->extractTokens(arg[0]);
  if (arg.size() > 1 && arg[1].empty() == false)
    passwords = this->extractTokens(arg[1]);
  pIt = passwords.begin();
  for (std::vector<std::string>::iterator it = channels.begin();
       it != channels.end(); it++)
  {
    if (pIt != passwords.end())
    {
      inPassword = *pIt;
      pIt++;
    }
    else
      inPassword = "";
    if ((*it)[0] != '#')
      return (sender.appendBufferOut(
          Replies::ERR_NOSUCHANNEL(sender.getNickname(), *it)));
    else if ((*it)[0] == '#' && (*it)[1])
    {
      Channel *chToJoin = chH.getChannelByName(*it);
      if (chToJoin == NULL)
      {
        chToJoin = chH.createChannel(*it);
        if (chToJoin == NULL)
          return;
      }
      if (chToJoin->canJoinChannel(sender, inPassword) == true)
      {
        chToJoin->addClient(&sender);
        chToJoin->replyJoinChannel(&sender);
      }
    }
  }
}

Join::~Join() {}
