#pragma once

#include <map>
#include <string>

class Channel;
class Client;

class ChannelHandler
{
private:
  std::map<std::string, Channel *> _channelList;
  ChannelHandler(const ChannelHandler &copy);
  ChannelHandler &operator=(const ChannelHandler &other);

public:
  ChannelHandler();

  Channel *getChannelByName(const std::string &name);
  Channel *getChannelName(Channel *channel);
  const std::map<std::string, Channel *> &getChannelList();

  void deleteChannel(std::string name);
  Channel *createChannel(const std::string &name);
  void deleteClient(Client *client);

  void createChannel(const std::string &name, Client *client);

  ~ChannelHandler();
};
