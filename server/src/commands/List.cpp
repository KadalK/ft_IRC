#include "commands/List.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

List::List() {}

void List::execute(Client &sender, ClientHandler &, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    const std::map<std::string, Channel *> channelList = chH.getChannelList();
    for (std::map<std::string, Channel *>::const_iterator it =
             channelList.begin();
         it != channelList.end(); it++)
    {
      sender.appendBufferOut(Replies::RPL_LIST(sender.getNickname(), it->first,
                                               it->second->getUserCountString(),
                                               it->second->getTopic()));
    }
    return (sender.appendBufferOut(Replies::RPL_LISTEND(sender.getNickname())));
  }
  std::vector<std::string> channels;
  channels = this->extractTokens(arg[0]);
  for (std::vector<std::string>::iterator it = channels.begin();
       it != channels.end(); it++)
  {
    Channel *channel = chH.getChannelByName(*it);
    if (channel)
    {
      sender.appendBufferOut(Replies::RPL_LIST(sender.getNickname(), *it,
                                               channel->getUserCountString(),
                                               channel->getTopic()));
    }
  }
  return (sender.appendBufferOut(Replies::RPL_LISTEND(sender.getNickname())));
}

List::~List() {}
