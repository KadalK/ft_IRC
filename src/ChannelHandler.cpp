#include "ChannelHandler.hpp"

ChannelHandler::ChannelHandler(){}

const char *ChannelHandler::NoChannelFound::what() const throw()
{
	return ("Channel not found");
}

const char *ChannelHandler::ChannelsEmpty::what() const throw()
{
	return ("Channels Empty");
}

Channel *ChannelHandler::getChannelByName(const std::string& name)
{
	std::vector<Channel*>::iterator it = this->_channelList.find(name);
		if (it == this->_channelList.end())
			throw NoChannelFound();
	return(it);
}

void ChannelHandler::deleteChannel(Channel *channel)
{
	std::vector<Channel*>::iterator it = this->_channelList.find(channel);
	if (it != this->_channelList.end())
	{
		this->_channelList.erase(it);
    delete *it;
	}
}

Channel* ChannelHandler::createChannel(const std::string& name, Client *client)
{
	std::map<std::string, Channel*>::iterator it = _channelList.find(name);
	if (it != this->_channelList.end())
		return *it;
	try
	{
		Channel* channel = new Channel(name, client);
    if (!channel)
      return NULL;
		this->_channelList.push_back(channel);
		return channel;
	}
	catch (const std::exception& e)
	{
		std::cout << "[ERROR] createChannel:" << e.what() << std::endl;
		return NULL;
	}
}

ChannelHandler::~ChannelHandler(){
	for (std::map<std::string, Channel*>::iterator it = _channel.begin(); it != _channel.end(); ++it)
		delete *it;
}
