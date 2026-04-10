#ifndef MANAGECHANNEL_HPP
#define MANAGECHANNEL_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include "Channel.hpp"
#include <map>

class ManageChannel{
private:
	std::map<std::string , Channel* > _channel;
public:
	ManageChannel();

	void deleteChannel(const std::string& name);
	Channel* createChannel(const std::string& name);
	~ManageChannel();
};

#endif