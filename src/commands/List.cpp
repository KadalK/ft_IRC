#include "commands/List.hpp"

List::List() {}

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

void List::execute(Client &client, ClientHandler &, ChannelHandler &chH,
                     const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    const std::map<std::string, Channel *> channelList = chH.getChannelList();
    for (std::map<std::string, Channel *>::const_iterator it =
             channelList.begin();
         it != channelList.end(); it++)
    {
        client.appendBufferOut(
          Replies::RPL_LIST(client.getNickname(), it->first, it->second->getUserCountString(), it->second->getTopic()));
    }
    return(client.appendBufferOut(
      Replies::RPL_LISTEND(client.getNickname())));
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
        Replies::RPL_LIST(client.getNickname(), *it, channel->getUserCountString(), channel->getTopic()));
    }
  }
  return(client.appendBufferOut(
    Replies::RPL_LISTEND(client.getNickname())));
}

List::~List() {}
