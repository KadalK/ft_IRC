#include "ManageChannel.hpp"

ManageChannel::ManageChannel(){}

void ManageChannel::deleteChannel(const std::string& name){
	std::map<std::string, Channel*>::iterator it = this->_channel.find(name);
	if (it != this->_channel.end())
	{
		delete it->second;
		this->_channel.erase(it);
	}
}

Channel* ManageChannel::createChannel(const std::string& name){
	std::map<std::string, Channel*>::iterator it = _channel.find(name);
	if (it != this->_channel.end())
		return it->second;
	try
	{
		Channel* channel = new Channel(name);
		this->_channel[name] = channel;
		return channel;
	}
	catch (const std::exception& e)
	{
		std::cout << "[ERROR] createChannel:" << e.what() << std::endl;
		return NULL;
	}
}

ManageChannel::~ManageChannel(){}