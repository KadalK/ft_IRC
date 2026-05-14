#include "commands/Part.hpp"
#include "Channel.hpp"

Part::Part() {}

// static std::string formatMsg(const Client &sender, const Client &target,
//                              const std::string &channelName,
//                              std::string &comment)
// {
//   std::string ret = ":" + sender.getNickname() + "!" + sender.getUsername() +
//                     "@" + sender.getHostname() + " Part " + channelName + " "
//                     + target.getNickname() + " :" + comment + "\r\n";
//   return (ret);
// }

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

void Part::execute(Client &client, ClientHandler &, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  std::string message = "";
  std::vector<std::string> channels;
  std::vector<std::string>::iterator it;
  Channel *channel;

  if (arg.size() < 1)
    return (client.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(client.getNickname(), "PART")));
  if (arg.size() >= 2)
    message = arg[1];
  channels = extractTokens(arg[0]);
  for (it = channels.begin(); it != channels.end(); ++it)
  {
    channel = chH.getChannelByName(*it);
    if (!channel)
    {
      client.appendBufferOut(
            Replies::ERR_NOSUCHANNEL(client.getNickname(), *it));
      continue;
    }
    if (channel->isClientInChannel(client) == false)
      {
        client.appendBufferOut(
            Replies::ERR_NOTONCHANNEL(client.getNickname(), *it));
        continue;
      }
    channel->broadcast(Replies::BC_PART(client.getFullName(),channel->getName(), message),&client, false);
    channel->removeClient(&client);
    if  (channel->getUserCount() == 0)
        chH.deleteChannel(channel->getName());
  }
}

Part::~Part() {}
