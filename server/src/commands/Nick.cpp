#include "commands/Nick.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "Replies.hpp"

Nick::Nick() {}

static bool validNick(const std::string &nick)
{
  if (!std::isalpha(static_cast<unsigned char>(nick[0])) && nick[0] != '_')
    return false;

  for (size_t i = 0; i < nick.size(); ++i)
  {
    if (!std::isalnum(static_cast<unsigned char>(nick[i])) && nick[i] != '_' &&
        nick[i] != '-')
      return false;
  }
  return true;
}

void Nick::execute(Client &sender, ClientHandler &clH, ChannelHandler &,
                   const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    sender.appendBufferOut(Replies::ERR_NONICKGIVEN(sender.getNickname()));
    return;
  }

  const std::string &nick = arg[0];
  if (!validNick(nick))
  {
    sender.appendBufferOut(
        Replies::ERR_ERRONEUSNICKNAME(sender.getNickname(), nick));
    return;
  }

  Client *existing = clH.getClientByNickname(nick);

  if (existing && existing != &sender)
  {
    sender.appendBufferOut(
        Replies::ERR_ERRONEUSNICKNAME(sender.getNickname(), nick));
    return;
  }
  sender.setNickname(nick);
  if (sender.getPassBool() && sender.getUserBool())
  {
    if (sender.getNickBool() == false)
      sender.setAuth(true);
  }
  sender.setNickBool(true);
}

Nick::~Nick() {}
