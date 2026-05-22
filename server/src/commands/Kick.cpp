#include "commands/Kick.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

Kick::Kick() {}

void Kick::execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  std::vector<std::string> targets;
  std::vector<std::string> channels;
  std::string comment;
  std::vector<std::string>::iterator tIt;
  std::vector<std::string>::iterator cIt;
  Channel *channel;
  Client *clientKicked;

  if (arg.size() < 2)
    return (sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "KICK")));
  channels = this->extractTokens(arg[0]);
  targets = this->extractTokens(arg[1]);
  if (channels.size() > 1 && channels.size() != targets.size())
    return (sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "KICK")));
  if (channels.size() == 1)
  {
    channel = chH.getChannelByName(channels[0]);
    if (!channel)
      return (sender.appendBufferOut(
          Replies::ERR_NOSUCHANNEL(sender.getNickname(), channels[0])));
    for (tIt = targets.begin(); tIt != targets.end(); tIt++)
    {
      if (channel->isClientInChannel(sender) == false)
        return (sender.appendBufferOut(Replies::ERR_NOTONCHANNEL(
            sender.getNickname(), channel->getName())));
      if (channel->isClientOperator(sender) == false)
      {
        sender.appendBufferOut(Replies::ERR_CHANNOPRIVSNEEDED(
            sender.getNickname(), channel->getName()));
        continue;
      }
      clientKicked = clH.getClientByNickname(*tIt);
      if (!clientKicked)
      {
        sender.appendBufferOut(
            Replies::ERR_NOSUCHNICK(sender.getNickname(), *tIt));
        continue;
      }
      if (channel->isClientInChannel(*clientKicked) == false)
      {
        sender.appendBufferOut(Replies::ERR_USERNOTINCHANNEL(
            sender.getNickname(), *tIt, channel->getName()));
        continue;
      }
      if (clientKicked->getNickname() == sender.getNickname())
        return;
      if (arg.size() >= 3)
        comment = arg[2];
      else
        comment = clientKicked->getNickname();
      channel->broadcast(Replies::BC_KICK(sender.getFullName(),
                                          clientKicked->getNickname(),
                                          channel->getName(), comment),
                         &sender, false);
      channel->removeClient(clientKicked);
    }
    return;
  }
  if (channels.size() == targets.size())
  {
    for (tIt = targets.begin(), cIt = channels.begin(); tIt != targets.end();
         tIt++, cIt++)
    {
      channel = chH.getChannelByName(*cIt);
      if (!channel)
      {
        sender.appendBufferOut(
            Replies::ERR_NOSUCHANNEL(sender.getNickname(), *cIt));
        continue;
      }
      if (channel->isClientInChannel(sender) == false)
      {
        sender.appendBufferOut(
            Replies::ERR_NOTONCHANNEL(sender.getNickname(), *cIt));
        continue;
      }
      if (channel->isClientOperator(sender) == false)
      {
        sender.appendBufferOut(
            Replies::ERR_CHANNOPRIVSNEEDED(sender.getNickname(), *cIt));
        continue;
      }
      clientKicked = clH.getClientByNickname(*tIt);
      if (!clientKicked)
      {
        sender.appendBufferOut(
            Replies::ERR_NOSUCHNICK(sender.getNickname(), *tIt));
        continue;
      }
      if (channel->isClientInChannel(*clientKicked) == false)
      {
        sender.appendBufferOut(
            Replies::ERR_USERNOTINCHANNEL(sender.getNickname(), *tIt, *cIt));
        continue;
      }
      if (clientKicked->getNickname() == sender.getNickname())
        continue;
      if (arg.size() >= 3)
        comment = arg[2];
      else
        comment = clientKicked->getNickname();
      channel->broadcast(Replies::BC_KICK(sender.getFullName(),
                                          clientKicked->getNickname(),
                                          channel->getName(), comment),
                         &sender, false);
      channel->removeClient(clientKicked);
    }
    return;
  }
}

Kick::~Kick() {}
