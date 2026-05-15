#include "commands/Topic.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

Topic::Topic() {}

void Topic::execute(Client &sender, ClientHandler &, ChannelHandler &chH,
                    const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    return (sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "TOPIC")));
  }
  const std::string &ChanName = arg[0];
  Channel *channel = chH.getChannelByName(ChanName);
  if (!channel)
  {
    return (sender.appendBufferOut(
        Replies::ERR_NOSUCHANNEL(sender.getNickname(), ChanName)));
  }
  if (channel->isClientInChannel(sender) == false)
  {
    return (sender.appendBufferOut(
        Replies::ERR_NOTONCHANNEL(sender.getNickname(), ChanName)));
  }
  if (arg.size() == 1)
  {
    if (channel->getHasTopic())
    {
      sender.appendBufferOut(Replies::RPL_TOPIC(sender.getNickname(),
                                                channel->getTopic(), ChanName));
    }
    else
    {
      sender.appendBufferOut(Replies::RPL_NOTOPIC(
          sender.getNickname(), channel->getTopic(), ChanName));
    }
  }
  if (channel->getTopicRestrict() && !channel->isClientOperator(sender))
  {
    return (sender.appendBufferOut(
        Replies::ERR_CHANNOPRIVSNEEDED(sender.getNickname(), ChanName)));
  }
  else
  {
    if (arg.size() >= 2)
    {
      std::string topic = arg[1];
      channel->setTopic(topic);
      channel->setTopicBool(true);
      channel->broadcast(Replies::BC_TOPIC(sender.getFullName(), ChanName,
                                           channel->getTopic()),
                         &sender, false);
    }
  }
}

Topic::~Topic() {}
