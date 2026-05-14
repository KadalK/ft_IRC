#include "commands/Names.hpp"

Names::Names() {}

static std::vector<std::string> extractTokens(const std::string &str)
{
  std::vector<std::string> v;
  size_t start = 0;
  size_t pos;
  while ((pos = str.find(",", start)) != std::string::npos)
  {
    if (!str.substr(start, pos - start).empty())
      v.push_back(str.substr(start, pos - start));
    start = pos + 1;
  }
  if (!str.substr(start).empty())
    v.push_back(str.substr(start));
  return (v);
}

void Names::execute(Client &client, ClientHandler &, ChannelHandler &chH,
                     const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    const std::map<std::string, Channel *> channelList = chH.getChannelList();
    for (std::map<std::string, Channel *>::const_iterator it =
             channelList.begin();
         it != channelList.end(); it++)
    {
      if (it->second->isClientInChannel(client) == true)
      {
        client.appendBufferOut(
          Replies::RPL_NAMREPLY(client.getNickname(), it->second->getClientInChan(), it->first));
        client.appendBufferOut(
          Replies::RPL_ENDOFNAMES(client.getNickname(), it->first));
      }
    }
    return ;
  }
  std::vector<std::string> channels;
  channels = extractTokens(arg[0]);
  for (std::vector<std::string>::iterator it = channels.begin();
       it != channels.end(); it++)
  {
    Channel *channel = chH.getChannelByName(*it);
    if (channel)
    {
      client.appendBufferOut(
        Replies::RPL_NAMREPLY(client.getNickname(), channel->getClientInChan(), *it));
      client.appendBufferOut(
        Replies::RPL_ENDOFNAMES(client.getNickname(), *it));
    }
  }
  return ;
}

Names::~Names() {}
