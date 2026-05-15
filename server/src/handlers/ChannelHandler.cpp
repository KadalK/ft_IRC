#include "ChannelHandler.hpp"
#include "Channel.hpp"
#include "Client.hpp"

ChannelHandler::ChannelHandler() {}

void ChannelHandler::deleteClient(Client *client)
{
  std::map<std::string, Channel *>::iterator it = this->_channelList.begin();

  while (it != this->_channelList.end())
  {
    it->second->removeClient(client);
    if (it->second->getUserCount() == 0)
    {
      delete it->second;
      this->_channelList.erase(it++);
    }
    else
      ++it;
  }
}

Channel *ChannelHandler::getChannelByName(const std::string &name)
{
  std::map<std::string, Channel *>::iterator it;

  it = this->_channelList.find(name);
  if (it == this->_channelList.end())
    return (NULL);
  return (it->second);
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

const std::map<std::string, Channel *> &ChannelHandler::getChannelList()
{
  return (this->_channelList);
}

Channel *ChannelHandler::createChannel(const std::string &name)
{

  std::map<std::string, Channel *>::iterator it;

  it = this->_channelList.find(name);
  if (it != this->_channelList.end())
    return (NULL);
  Channel *channel = new Channel(name);
  if (!channel)
    return (NULL);
  this->_channelList[name] = channel;
  return (channel);
}

ChannelHandler::~ChannelHandler()
{
  for (std::map<std::string, Channel *>::iterator it =
           this->_channelList.begin();
       it != this->_channelList.end(); ++it)
    delete it->second;
}
