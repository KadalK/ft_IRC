#include "commands/Nick.hpp"
#include <iostream>

Nick::Nick() {}

// TODO:
//    replies
//            ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//			 ERR_NICKNAMEINUSE               ERR_NICKCOLLISION

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
//
void Nick::execute(Client &client, ClientHandler &clH, ChannelHandler &,
                   const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    client.appendBufferOut(Replies::ERR_NONICKGIVEN(client.getNickname()));
    return;
  }

  const std::string &nick = arg[0];
  if (!validNick(nick))
  {
    client.appendBufferOut(Replies::ERR_ERRONEUSNICKNAME(client.getNickname(), nick));
    return;
  }

  Client *existing = clH.getClientByNickname(nick);

  if (existing && existing != &client)
  {
    client.appendBufferOut(Replies::ERR_ERRONEUSNICKNAME(client.getNickname(), nick));
    return;
  }
  client.setNickname(nick);
  if (client.getPassBool() && client.getUserBool())
  {
    if (client.getNickBool() == false)
      client.setAuth(true);
  }
  client.setNickBool(true);
  return;
}

Nick::~Nick() {}
