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

	class NoChannelFound : public std::exception{
		virtual const char* what() const throw();
	};

	class ChannelsEmpty : public std::exception{
		virtual const char* what() const throw();
	};

	Channel* getChannel(const std::string& name);
	std::map<std::string , Channel* > getAllChannels();
	void	deleteChannel(const std::string& name);
	Channel* createChannel(const std::string& name);
	~ManageChannel();
};

#endif