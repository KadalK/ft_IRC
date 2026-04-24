#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "Channel.hpp"
#include "Client.hpp"
#include <map>

class ChannelHandler{
private:
	std::map<std::string, Channel *> _channelList;
	ChannelHandler(const ChannelHandler& copy);
	ChannelHandler& operator=(const ChannelHandler& other);
public:
	ChannelHandler();

	//Exeptions
	class NoChannelFound : public std::exception{
		virtual const char* what() const throw();
	};
	class ChannelsEmpty : public std::exception{
		virtual const char* what() const throw();
	};

	//Getters
	Channel *getChannelByName(const std::string& name);
	Channel *getChannelName(Channel *channel);

	//Methods
	void	deleteChannel(std::string name);
	void createChannel(const std::string& name, Client *client);

	~ChannelHandler();
};
