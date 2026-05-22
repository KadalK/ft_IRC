#include "commands/Part.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "Replies.hpp"

Part::Part() {}

void Part::execute(Client &sender, ClientHandler &, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  std::string message = "";
  std::vector<std::string> channels;
  std::vector<std::string>::iterator it;
  Channel *channel;

  if (arg.size() < 1)
    return (sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "PART")));
  if (arg.size() >= 2)
    message = arg[1];
  channels = this->extractTokens(arg[0]);
  for (it = channels.begin(); it != channels.end(); ++it)
  {
    channel = chH.getChannelByName(*it);
    if (!channel)
    {
      sender.appendBufferOut(
          Replies::ERR_NOSUCHANNEL(sender.getNickname(), *it));
      continue;
    }
    if (channel->isClientInChannel(sender) == false)
    {
      sender.appendBufferOut(
          Replies::ERR_NOTONCHANNEL(sender.getNickname(), *it));
      continue;
    }
    channel->broadcast(
        Replies::BC_PART(sender.getFullName(), channel->getName(), message),
        &sender, false);
    channel->removeClient(&sender);
    if (channel->getUserCount() == 0)
      chH.deleteChannel(channel->getName());
  }
}

Part::~Part() {}
