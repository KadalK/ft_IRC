#include "commands/Kick.hpp"
#include "Channel.hpp"

Kick::Kick() {}

// static std::string formatMsg(const Client &sender, const Client &target,
//                              const std::string &channelName,
//                              std::string &comment)
// {
//   std::string ret = ":" + sender.getNickname() + "!" + sender.getUsername() +
//                     "@" + sender.getHostname() + " KICK " + channelName + " "
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

void Kick::execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  std::vector<std::string> targets;
  std::vector<std::string> channels;
  std::string comment;
  std::vector<std::string>::iterator tIt;
  std::vector<std::string>::iterator cIt;
  Channel *channel;
  Client *clientKicked;

  if (arg.size() < 2)
    return (client.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(client.getNickname(), "KICK")));
  channels = extractTokens(arg[0]);
  targets = extractTokens(arg[1]);
  if (channels.size() > 1 && channels.size() != targets.size())
    return (client.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(client.getNickname(), "KICK")));
  if (channels.size() == 1)
  {
    channel = chH.getChannelByName(channels[0]);
    if (!channel)
      return (client.appendBufferOut(
          Replies::ERR_NOSUCHANNEL(client.getNickname(), channels[0])));
    for (tIt = targets.begin(); tIt != targets.end(); tIt++)
    {
      if (channel->isClientInChannel(client) == false)
        return (client.appendBufferOut(Replies::ERR_NOTONCHANNEL(
            client.getNickname(), channel->getName())));
      if (channel->isClientOperator(client) == false)
      {
        client.appendBufferOut(Replies::ERR_CHANNOPRIVSNEEDED(
            client.getNickname(), channel->getName()));
        continue;
      }
      clientKicked = clH.getClientByNickname(*tIt);
      if (!clientKicked)
      {
        client.appendBufferOut(
            Replies::ERR_NOSUCHNICK(client.getNickname(), *tIt));
        continue;
      }
      if (channel->isClientInChannel(*clientKicked) == false)
      {
        client.appendBufferOut(Replies::ERR_USERNOTINCHANNEL(
            client.getNickname(), *tIt, channel->getName()));
        continue;
      }
      if (arg.size() >= 3)
        comment = arg[2];
      else
        comment = clientKicked->getNickname();
      channel->broadcast(Replies::BC_KICK(client.getFullName(),
                                          clientKicked->getNickname(),
                                          channel->getName(), comment),
                         &client, false);
      channel->removeClient(clientKicked);
      std::cout << channel->getClientInChan() << std::endl;
    }
    return;
  }
  if (channels.size() == targets.size())
  {
    for (tIt = targets.begin(), cIt = channels.begin(); tIt != targets.end();
         tIt++, cIt++)
    {
      channel = chH.getChannelByName(*cIt);
      if (!channel)
      {
        client.appendBufferOut(
            Replies::ERR_NOSUCHANNEL(client.getNickname(), *cIt));
        continue;
      }
      if (channel->isClientInChannel(client) == false)
      {
        client.appendBufferOut(
            Replies::ERR_NOTONCHANNEL(client.getNickname(), *cIt));
        continue;
      }
      if (channel->isClientOperator(client) == false)
      {
        client.appendBufferOut(
            Replies::ERR_CHANNOPRIVSNEEDED(client.getNickname(), *cIt));
        continue;
      }
      clientKicked = clH.getClientByNickname(*tIt);
      if (!clientKicked)
      {
        client.appendBufferOut(
            Replies::ERR_NOSUCHNICK(client.getNickname(), *tIt));
        continue;
      }
      if (channel->isClientInChannel(*clientKicked) == false)
      {
        client.appendBufferOut(
            Replies::ERR_USERNOTINCHANNEL(client.getNickname(), *tIt, *cIt));
        continue;
      }
      if (arg.size() >= 3)
        comment = arg[2];
      else
        comment = clientKicked->getNickname();
      channel->broadcast(Replies::BC_KICK(client.getFullName(),
                                          clientKicked->getNickname(),
                                          channel->getName(), comment),
                         &client, false);
      channel->removeClient(clientKicked);
    }
    return;
  }
}

Kick::~Kick() {}
