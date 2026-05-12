#include "commands/PrivMsg.hpp"
#include "Commands.hpp"
#include <sstream>
#include <string>

#include "Client.hpp"
#include "Replies.hpp"

// PrivMsg::PrivMsg() {}
// PrivMsg::PrivMsg(PrivMsg const &src) { (void)src; }
// PrivMsg::~PrivMsg() {};
// PrivMsg &PrivMsg::operator=(PrivMsg const &rhs) { (void)rhs; }
//
// void PrivMsg::execute(Client*, std::vector<std::string>)
// {
//
//   if (this->parsingMessage(p, rawText) != 0)
//     return (-1);//throw exception plus tard quoi en gros + errorMessage()
//
// }
//
// void parsingNickNames(std::string ){}
//
// size_t PrivMsg::parsingMessage(std::string rawText)
// {
//   size_t pos = rawText.find(':');
//   parsingNickNames(rawText.substr(0, pos));
//   p.textMessage = rawText + pos;

static std::string intToString(size_t value)
{
  std::stringstream ss;
  ss << value;

  return (ss.str());
}

PrivMsg::PrivMsg() {}

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

std::string formatMsg(const std::string &msg, const std::string &sender,
                      const std::string &target)
{
  return (":" + sender + " PRIVMSG " + target + " :" + msg + "\r\n");
}

void PrivMsg::execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
                      const std::vector<std::string> &arg)
{
  if (arg.empty())
    return (client.appendBufferOut(
        Replies::ERR_NORECIPIENT(client.getNickname(), "PRIVMSG")));
  if (arg.size() < 2)
    return (client.appendBufferOut(
        Replies::ERR_NOTEXTTOSEND(client.getNickname())));
  std::vector<std::string> targets = extractTokens(arg[0]);
  if (targets.size() > 4)
  {
    client.appendBufferOut(
        Replies::ERR_TOOMANYTARGETS(arg[0], intToString(targets.size())));
    return (
        client.appendBufferOut(Replies::RPL_ISUPPORT(client.getNickname())));
  }

  const std::string &msg = arg[1];

  for (std::vector<std::string>::iterator it = targets.begin();
       it != targets.end(); ++it)
  {
    const std::string &target = *it;

    std::string formatted = formatMsg(msg, client.getNickname(), target);
    if (target[0] == '#')
    {

      Channel *chan = chH.getChannelByName(target);
      if (!chan)
      {
        client.appendBufferOut(
            Replies::ERR_NOSUCHANNEL(client.getNickname(), target));
        continue;
      }
      chan->broadcast(
          Replies::BC_PRIVMSG(client.getFullName(), chan->getName(), msg),
          &client, true);
    }
    else
    {
      Client *receiver = clH.getClientByNickname(target);
      if (!receiver)
      {
        client.appendBufferOut(
            Replies::ERR_NOSUCHNICK(client.getFullName(), target));
        continue;
      }
      if (!receiver->getAuth())
        continue;
      receiver->appendBufferOut(
          Replies::BC_PRIVMSG(client.getFullName(), target, msg));
    }
  }
}

PrivMsg::~PrivMsg() {}
