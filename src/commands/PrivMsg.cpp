#include "commands/PrivMsg.hpp"
#include "Channel.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"
#include <sstream>

static std::string intToString(size_t value)
{
  std::stringstream ss;
  ss << value;

  return (ss.str());
}

PrivMsg::PrivMsg() {}

std::string formatMsg(const std::string &msg, const std::string &sender,
                      const std::string &target)
{
  return (":" + sender + " PRIVMSG " + target + " :" + msg + "\r\n");
}

void PrivMsg::execute(Client &sender, ClientHandler &clH, ChannelHandler &chH,
                      const std::vector<std::string> &arg)
{
  if (arg.empty())
    return (sender.appendBufferOut(
        Replies::ERR_NORECIPIENT(sender.getNickname(), "PRIVMSG")));
  if (arg.size() < 2)
    return (sender.appendBufferOut(
        Replies::ERR_NOTEXTTOSEND(sender.getNickname())));
  std::vector<std::string> targets = this->extractTokens(arg[0]);
  if (targets.size() > 4)
  {
    sender.appendBufferOut(
        Replies::ERR_TOOMANYTARGETS(arg[0], intToString(targets.size())));
    return (
        sender.appendBufferOut(Replies::RPL_ISUPPORT(sender.getNickname())));
  }

  const std::string &msg = arg[1];

  for (std::vector<std::string>::iterator it = targets.begin();
       it != targets.end(); ++it)
  {
    const std::string &target = *it;

    std::string formatted = formatMsg(msg, sender.getNickname(), target);
    if (target[0] == '#')
    {

      Channel *chan = chH.getChannelByName(target);
      if (!chan)
      {
        sender.appendBufferOut(
            Replies::ERR_NOSUCHANNEL(sender.getNickname(), target));
        continue;
      }
      chan->broadcast(
          Replies::BC_PRIVMSG(sender.getFullName(), chan->getName(), msg),
          &sender, true);
    }
    else
    {
      Client *receiver = clH.getClientByNickname(target);
      if (!receiver)
      {
        sender.appendBufferOut(
            Replies::ERR_NOSUCHNICK(sender.getFullName(), target));
        continue;
      }
      if (!receiver->getAuth())
        continue;
      receiver->appendBufferOut(
          Replies::BC_PRIVMSG(sender.getFullName(), target, msg));
    }
  }
}

PrivMsg::~PrivMsg() {}
