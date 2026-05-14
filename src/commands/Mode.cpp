#include "commands/Mode.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

Mode::Mode() {}

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

static bool validParamsCount(const std::string &flags,
                             std::vector<std::string>::const_iterator start,
                             std::vector<std::string>::const_iterator end)
{
  size_t flagsCount = 0;
  size_t paramCount = std::distance(start, end);
  bool sign = false;
  for (size_t i = 0; i < flags.size(); i++)
  {
    if (flags[i] == '+')
      sign = true;
    if (flags[i] == '-')
      sign = false;
    if (flags[i] == 'k' || flags[i] == 'o')
      flagsCount += 1;
    if (flags[i] == 'l' && sign == true)
      flagsCount += 1;
  }
  return (flagsCount <= paramCount);
}

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
    return ('P');
  case '-':
    return ('M');
  default:
    return ('U');
  }
}

static void listModes(Channel &channel, Client &sender)
{
  std::string modeString = channel.getModeString();
  sender.appendBufferOut(Replies::RPL_CHANNELMODEIS(
      sender.getNickname(), channel.getName(), modeString));
  return;
}

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

void Mode::execute(Client &sender, ClientHandler &, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  oldState old;
  Channel *channel;
  std::string flags;
  std::string param;
  std::vector<std::string>::const_iterator it;
  bool sign;
  size_t type;
  size_t paramApplied;

  if (arg.empty())
    return;
  channel = chH.getChannelByName(arg[0]);
  if (!channel)
    return (sender.appendBufferOut(
        Replies::ERR_NOSUCHANNEL(sender.getNickname(), arg[0])));
  if (channel->isClientInChannel(sender) == false)
    return (sender.appendBufferOut(
        Replies::ERR_NOTONCHANNEL(sender.getNickname(), arg[0])));
  if (arg.size() == 1)
    return (listModes(*channel, sender));
  if (channel->isClientOperator(sender) == false)
    return (sender.appendBufferOut(
        Replies::ERR_CHANNOPRIVSNEEDED(sender.getNickname(), arg[0])));
  flags = arg[1];
  if (flags[0] != '-' && flags[0] != '+')
    return (sender.appendBufferOut(
        Replies::ERR_UNKNOWNMODE(sender.getNickname(), flags[0])));
  if (arg.size() >= 3)
  {
    it = arg.begin() + 2;
    param = *it;
  }
  else
    it = arg.end();
  if (validParamsCount(flags, it, arg.end()) == false)
    return (sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "MODE")));

  old.topicRestrict = channel->getTopicRestrict();
  old.inviteOnly = channel->getInviteOnly();
  old.hasUserLimit = channel->getHasUserLimit();
  old.hasPassword = channel->getHasPassword();
  old.password = channel->getPassword();
  old.userLimit = channel->getUserLimit();
  old.clients = channel->getClients();
  sign = (flags[0] == '+');
  paramApplied = 0;
  for (size_t i = 1; i < flags.size(); i++)
  {
    type = getFlagType(flags[i]);
    if (type == 'U')
      return (sender.appendBufferOut(
          Replies::ERR_UNKNOWNMODE(sender.getNickname(), flags[i])));
    if (type == 'P')
      sign = true;
    else if (type == 'M')
      sign = false;
    else
    {
      if (((type == 'C' && sign == true) || type == 'B') && it != arg.end() &&
          paramApplied < 3)
      {
        param = *it++;
        paramApplied++;
      }
      else
        param = "";
      (channel->*channel->_modeFt[flags[i]])(sign, param, &sender);
    }
  }
  std::string modeString = listModesChanges(old, *channel);
  if (!modeString.empty())
    channel->broadcast(
        Replies::BC_MODE(sender.getFullName(), channel->getName(), modeString),
        &sender, false);
}

Mode::~Mode() {}
