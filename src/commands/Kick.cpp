#include "commands/Kick.hpp"
#include "Channel.hpp"

Kick::Kick() {}

static std::string formatMsg(const Client &sender, const Client &target,
                             const std::string &channelName,
                             std::string &comment)
{
  std::string ret = ":" + sender.getNickname() + "!" + sender.getUsername() +
                    "@" + sender.getHostname() + " KICK " + channelName + " " +
                    target.getNickname() + " :" + comment + "\r\n";
  return (ret);
}

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
  {
    // 461 "<client> <command> :Not enough parameters"
    std::cout << "not enough params" << std::endl;
    return;
  }
  channels = extractTokens(arg[0]);
  targets = extractTokens(arg[1]);
  if (channels.size() > 1 && channels.size() != targets.size())
  {
    // 461 "<client> <command> :Not enough parameters"
    std::cout << "Syntax error" << std::endl;
    return;
  }
  if (channels.size() == 1)
  {
    channel = chH.getChannelByName(channels[0]);
    if (!channel)
    {
      std::cout << "No such channel" << std::endl;
      // 403 "<client> <channel> :No such channel"
      return;
    }
    for (tIt = targets.begin(); tIt != targets.end(); tIt++)
    {
      if (channel->isClientInChannel(client) == false)
      {
        std::cout << " you are not in this channel" << std::endl;
        // 442 "<client> <nick> <channel> :You're not on that channel"
        continue;
      }
      if (channel->isClientOperator(client) == false)
      {
        std::cout << "not operator" << std::endl;
        // 482 "<client> <channel> :You're not channel operator"
        continue;
      }
      clientKicked = clH.getClientByNickname(*tIt);
      if (!clientKicked)
      {
        std::cout << "No such nickname" << std::endl;
        // 401 "<client> :No such nickname"
        continue;
      }
      if (channel->isClientInChannel(*clientKicked) == false)
      {
        std::cout << " user not in channel" << std::endl;
        // 441 "<client> <nick> <channel> :They aren't on that channel"
        continue;
      }
      if (arg.size() >= 3)
        comment = arg[2];
      else
        comment = clientKicked->getNickname();
      channel->removeClient(clientKicked);
      std::string reply =
          formatMsg(client, *clientKicked, channel->getName(), comment);
      std::cout << reply << std::endl;
      channel->broadcast(reply, &client);
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
        std::cout << "No such channel" << std::endl;
        // 403 "<client> <channel> :No such channel"
        return;
      }
      if (channel->isClientInChannel(client) == false)
      {
        std::cout << " you are not in this channel" << std::endl;
        // 442 "<client> <nick> <channel> :You're not on that channel"
        continue;
      }
      if (channel->isClientOperator(client) == false)
      {
        std::cout << "not operator" << std::endl;
        // 482 "<client> <channel> :You're not channel operator"
        continue;
      }
      clientKicked = clH.getClientByNickname(*tIt);
      if (!clientKicked)
      {
        std::cout << "No such nickname" << std::endl;
        // 401 "<client> :No such nickname"
        continue;
      }
      if (channel->isClientInChannel(*clientKicked) == false)
      {
        std::cout << " user not in channel" << std::endl;
        // 441 "<client> <nick> <channel> :They aren't on that channel"
        continue;
      }
      if (arg.size() >= 3)
        comment = arg[2];
      else
        comment = clientKicked->getNickname();
      channel->removeClient(clientKicked);
      std::string reply =
          formatMsg(client, *clientKicked, channel->getName(), comment);
      std::cout << reply << std::endl;
      channel->broadcast(reply, &client);
    }
    return;
  }
}

Kick::~Kick() {}
