#pragma once

#include "Channel.hpp"
#include "Client.hpp"
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class ChannelHandler
{
private:
  std::map<std::string, Channel *> _channelList;
  ChannelHandler(const ChannelHandler &copy);
  ChannelHandler &operator=(const ChannelHandler &other);

public:
  ChannelHandler();

  // Getters
  Channel *getChannelByName(const std::string &name);
  Channel *getChannelName(Channel *channel);
  const std::map<std::string, Channel *> &getChannelList();

  // Methods
  void deleteChannel(std::string name);
  Channel *createChannel(const std::string &name);
  void deleteClient(Client *client);

	//Methods
	void  createChannel(const std::string& name, Client *client);

  /*
  FONCTION BROADCAST : transmet le message a tous les FD necessaires
  */

  ~ChannelHandler();
};
