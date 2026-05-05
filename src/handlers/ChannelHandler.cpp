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

void ChannelHandler::deleteClient(Client *client)
{
	std::map<std::string,Channel *>:: iterator it;

	for (it = this->_channelList.begin(); it != this->_channelList.end(); ++it)
	{
		it->second->removeClient(client);
		if (it->second->getUserCount() == 0)
		{
				delete it->second;
				this->_channelList.erase(it);
		}
	}
}

Channel *ChannelHandler::getChannelByName(const std::string& name)
{
	std::map<std::string, Channel *>::iterator it;

  it = this->_channelList.find(name);
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

Channel *ChannelHandler::createChannel(const std::string& name)
{

	std::map<std::string, Channel *>::iterator it;

  it = this->_channelList.find(name);
	if (it != this->_channelList.end())
		return (NULL);
	try
	{
		Channel* channel = new Channel(name);
    if (!channel)
      return (NULL);
		this->_channelList[name] = channel;
		return (channel);
	}
	catch (const std::exception& e)
	{
		std::cout << "[ERROR] createChannel:" << e.what() << std::endl;
		return (NULL);
	}
}

ChannelHandler::~ChannelHandler(){
	for (std::map<std::string, Channel*>::iterator it = this->_channelList.begin(); it != this->_channelList.end(); ++it)
		delete it->second;
}
