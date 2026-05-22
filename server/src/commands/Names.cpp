#include "commands/Names.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "Replies.hpp"

Names::Names() {}

void Names::execute(Client &sender, ClientHandler &, ChannelHandler &chH,
                    const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    const std::map<std::string, Channel *> channelList = chH.getChannelList();
    for (std::map<std::string, Channel *>::const_iterator it =
             channelList.begin();
         it != channelList.end(); it++)
    {
      if (it->second->isClientInChannel(sender) == true)
      {
        sender.appendBufferOut(Replies::RPL_NAMREPLY(
            sender.getNickname(), it->second->getClientInChan(), it->first));
        sender.appendBufferOut(
            Replies::RPL_ENDOFNAMES(sender.getNickname(), it->first));
      }
    }
    return;
  }
  std::vector<std::string> channels;
  channels = this->extractTokens(arg[0]);
  for (std::vector<std::string>::iterator it = channels.begin();
       it != channels.end(); it++)
  {
    Channel *channel = chH.getChannelByName(*it);
    if (channel)
    {
      sender.appendBufferOut(Replies::RPL_NAMREPLY(
          sender.getNickname(), channel->getClientInChan(), *it));
      sender.appendBufferOut(
          Replies::RPL_ENDOFNAMES(sender.getNickname(), *it));
    }
  }
}

Names::~Names() {}
