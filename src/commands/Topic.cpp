#include "commands/Topic.hpp"

Topic::Topic() {}

void Topic::parsingMessage(std::string rawText) { (void)rawText; }

void Topic::execute(Client &client, ClientHandler &, ChannelHandler &chH,
                    const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    return (client.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(client.getNickname(), "TOPIC")));
  }
  const std::string &ChanName = arg[0];
  Channel *channel = chH.getChannelByName(ChanName);
  if (!channel)
  {
    return (client.appendBufferOut(
        Replies::ERR_NOSUCHANNEL(client.getNickname(), ChanName)));
  }
  if (channel->isClientInChannel(client) == false)
  {
    return (client.appendBufferOut(
        Replies::ERR_NOTONCHANNEL(client.getNickname(), ChanName)));
  }
  if (arg.size() == 1)
  {
    if (channel->getHasTopic())
      {
        client.appendBufferOut(Replies::RPL_TOPIC(
        client.getNickname(), channel->getTopic(), ChanName));
      }
    else
    {
      client.appendBufferOut(Replies::RPL_NOTOPIC(
        client.getNickname(), channel->getTopic(), ChanName));
    }
  }
  if (channel->getTopicRestrict() && !channel->isClientOperator(client))
  {
    return (client.appendBufferOut(
        Replies::ERR_CHANNOPRIVSNEEDED(client.getNickname(), ChanName)));
  }
  else
  {
    if (arg.size() >= 2)
    {
      std::string topic = arg[1] + "\r\n";
      channel->setTopic(topic);
      channel->setTopicBool(true);
      channel->broadcast(Replies::BC_TOPIC(client.getFullName(), ChanName,channel->getTopic()),&client, false);
    }
  }
}

void Topic::errorMessage(size_t errorValue) { (void)errorValue; }

Topic::~Topic() {}
