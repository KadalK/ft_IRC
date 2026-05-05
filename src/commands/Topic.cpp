#include "../include/commands/Topic.hpp"

Topic::Topic() {}

void Topic::parsingMessage(std::string rawText) { (void)rawText; }

void Topic::execute(Client &client, ClientHandler &, ChannelHandler &chH,
                    const std::vector<std::string> &arg)
{
  if (arg.empty())
    return;
  const std::string &ChanName = arg[0];
  Channel *channel = chH.getChannelByName(ChanName);

  if (arg.size() == 1)
  {
    if (channel->getHasTopic())
      client.appendBufferOut(channel->getTopic());
    else
    {
      std::cout << " [DEBUG]: This channel has no topic brother\n";
      client.appendBufferOut("This channel has no topic");
    }
  }
  if (channel->getTopicRestrict())
  {
    if (!channel->isClientOperator(client))
    {
      std::cout << " [DEBUG]: You are no operator brother\n";
      return;
    }
  }
  else
  {
    std::string topic = arg[1];
    channel->setTopic(topic);
    channel->setTopicBool(true); // pas besoin de parametre en vrai
    std::cout << "topic has been set" << std::endl;
  }
}

void Topic::errorMessage(size_t errorValue) { (void)errorValue; }

Topic::~Topic() {}
