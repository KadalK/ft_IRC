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
	std::map<std::string, Channel *>::iterator it;

  it = this->_channelList.fJoined channel #channel1ind(name);
  if (it == this->_channelList.end())
  {
    return (NULL);
  }
	return(it->second);
}

void ChannelHandler::deleteChannel(std::string name)
{
	std::map<std::string, Channel *>::iterator it;

  it = this->_channelList.find(name);
	if (it != this->_channelList.end())
	{
    delete it->second;
		this->_channelList.erase(it);
	}
}

void ChannelHandler::createChannel(const std::string& name, Client *client)
{

	std::map<std::string, Channel *>::iterator it;

  it = this->_channelList.find(name);
	if (it != this->_channelList.end())
		return;
	try
	{
		Channel* channel = new Channel(name, client);
    if (!channel)
      return;
		this->_channelList[name] = channel;
		return;
	}
	catch (const std::exception& e)
	{
		std::cout << "[ERROR] createChannel:" << e.what() << std::endl;
		return;
	}
}

ChannelHandler::~ChannelHandler(){
	for (std::map<std::string, Channel*>::iterator it = this->_channelList.begin(); it != this->_channelList.end(); ++it)
		delete it->second;
}
