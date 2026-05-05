#include "../include/commands/Topic.hpp"

Topic::Topic(){}


void Topic::parsingMessage(std::string rawText){
	(void)rawText;
}

void Topic::execute(Client& client, ClientHandler &clH, ChannelHandler &chH, const std::vector<std::string>& arg){
	if (arg.size() < 2)
		return;

	const std::string& ChanName = arg[0];
	Channel* channel = chH.getChannelByName(ChanName);

	if (channel.isClientOperator())
	{
		if (arg.empty())
		{
			if (channel->getHasTopic())
				client.appendBufferOut(channel->getTopic());
			else
			{
				std::cout << " [DEBUG]: This channel has no topic brother\n";
				client.appendBufferOut("This channel has no topic");
			}
		}
		else
		{
			std::string topic = arg[1];
			channel->setTopic(topic);
		}
	}
}

void Topic::errorMessage(size_t errorValue){
	(void)errorValue;
}

Topic::~Topic(){}

