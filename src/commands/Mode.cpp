#include "commands/Mode.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"

Mode::Mode() {}

static size_t getFlagType(char c)
{
  switch (c)
  {
  case 'k':
  case 'o':
    return ('B');
  case 'l':
    return ('C');
  case 'i':
  case 't':
    return ('D');
  case '+':
  case '-':
    return ('S');
  default:
    return ('U');
  }
}

void listModes(Channel &channel, Client &client)
{
  std::string modeString = channel.getModeString();
  client.appendBufferOut(Replies::RPL_CHANNELMODEIS(
      client.getNickname(), channel.getName(), modeString));
  // client.appendBufferOut(Replies::RPL_CREATIONTIME(client.getNickname(),
  // channel.getName()));
  return;
}

struct oldState
{
  bool topicRestrict;
  bool inviteOnly;
  bool hasPassword;
  std::string password;
  bool hasUserLimit;
  size_t userLimit;
  std::map<Client *, bool> clients;
};

static std::string listModesChanges(oldState &old, Channel &channel)
{
  std::string addedFlags = "+";
  std::string removedFlags = "-";
  std::string params = "";
  std::string modeString = "";

  if (old.inviteOnly != channel.getInviteOnly())
    (channel.getInviteOnly() ? addedFlags : removedFlags) += "i";
  if (old.topicRestrict != channel.getTopicRestrict())
    (channel.getTopicRestrict() ? addedFlags : removedFlags) += "t";
  if (old.hasPassword != channel.getHasPassword())
  {
    (channel.getHasPassword() ? addedFlags : removedFlags) += "k";
    params +=
        " " + (channel.getHasPassword() ? channel.getPassword() : old.password);
  }
  if (old.userLimit != channel.getUserLimit())
  {
    (channel.getHasUserLimit() ? addedFlags : removedFlags) += "l";
    params +=
        (channel.getHasUserLimit() ? " " + channel.getUserLimitString() : "");
  }
  std::map<Client *, bool>::const_iterator it;
  std::map<Client *, bool>::iterator oIt;
  for (it = channel.getClients().begin(), oIt = old.clients.begin();
       oIt != old.clients.end(); it++, oIt++)
  {
    if (it->second != oIt->second)
    {
      (it->second ? addedFlags : removedFlags) += "o";
      params += " " + it->first->getNickname();
    }
  }
  if (addedFlags.size() != 1)
    modeString += addedFlags;
  if (removedFlags.size() != 1)
    modeString += removedFlags;
  if (!params.empty())
    modeString += params;
  return (modeString);
}

void Mode::execute(Client &client, ClientHandler &, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  oldState old;
  Channel *channel;
  std::string flags;
  std::string param;
  std::vector<std::string>::const_iterator it;
  bool sign;
  size_t type;

  channel = chH.getChannelByName(arg[0]);
  if (!channel)
    return (client.appendBufferOut(
        Replies::ERR_NOSUCHANNEL(client.getNickname(), arg[0])));
  if (channel->isClientInChannel(client) == false)
    return (client.appendBufferOut(
        Replies::ERR_NOTONCHANNEL(client.getNickname(), arg[0])));
  if (arg.size() == 1)
    return (listModes(*channel, client));
  if (channel->isClientOperator(client) == false)
    return (client.appendBufferOut(
        Replies::ERR_CHANNOPRIVSNEEDED(client.getNickname(), arg[0])));
  flags = arg[1];
  if (flags[0] != '-' && flags[0] != '+')
    return (client.appendBufferOut(
        Replies::ERR_UNKNOWNMODE(client.getNickname(), flags[0])));
  // Compter si il y a bien autant de param que de flags en necessitant
  old.topicRestrict = channel->getTopicRestrict();
  old.inviteOnly = channel->getInviteOnly();
  old.hasUserLimit = channel->getHasUserLimit();
  old.hasPassword = channel->getHasPassword();
  old.password = channel->getPassword();
  old.userLimit = channel->getUserLimit();
  old.clients = channel->getClients();

  sign = (flags[0] == '+');
  if (arg.size() >= 3)
  {
    it = arg.begin() + 2;
    param = *it;
  }
  else
  {
    it = arg.end();
    param = "";
  }
  for (size_t i = 1; i < flags.size(); i++)
  {
    type = getFlagType(flags[i]);
    if (type == 'U')
      return (client.appendBufferOut(
          Replies::ERR_UNKNOWNMODE(client.getNickname(), flags[i])));
    if (flags[i] == '+')
      sign = true;
    else if (flags[i] == '-')
      sign = false;
    else
    {
      // MAXIMUM 3 PARAM AVEC FLAG DONC verifier count < 3
      if (((type == 'C' && sign == true) || type == 'B') && it != arg.end())
        param = *it++;
      else
        param = "";
      (channel->*channel->_modeFt[flags[i]])(sign, param, &client);
    }
  }
  std::string modeString = listModesChanges(old, *channel);
  if (!modeString.empty())
    channel->broadcast(
        Replies::BC_MODE(client.getNickname(), channel->getName(), modeString),
        &client);
}

Mode::~Mode() {}
