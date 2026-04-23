#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "Channel.hpp"
#include <map>

class ManageChannel{
private:
	std::map<std::string , Channel* > _channel;
	ManageChannel(const ManageChannel& copy);
	ManageChannel& operator=(const ManageChannel& other);
public:
	ManageChannel();

	//Exeptions
	class NoChannelFound : public std::exception{
		virtual const char* what() const throw();
	};
	class ChannelsEmpty : public std::exception{
		virtual const char* what() const throw();
	};

	//Getters
	Channel* getChannel(const std::string& name);
	std::map<std::string , Channel* >& getAllChannels();

	//Methods
	void	deleteChannel(const std::string& name);
	Channel* createChannel(const std::string& name);

	~ManageChannel();
};

#endif
