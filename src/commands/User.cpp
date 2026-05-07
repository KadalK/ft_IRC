#include "commands/User.hpp"

User::User() {}

// TODO
//  ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

static bool parsingUsername(std::string str)
{
  size_t i;
  const char badChar[] = {' ', '@', '!', '\0', '\r', '\n'};

  i = str.find_first_of(badChar, 0, 6);
  if (i != std::string::npos)
    return (false); // set BuffOut bad USERNAME
  return (true);
}

void User::execute(Client &client, ClientHandler &, ChannelHandler &,
                   const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    client.appendBufferOut(Replies::ERR_NEEDMOREPARAMS(client.getNickname(), "USER"));
    return;
  }
  if (client.getUserBool())
  {
    client.appendBufferOut(Replies::ERR_ALREADYREGISTERED(client.getNickname()));
    return;
  }
  if (parsingUsername(arg[0]) == false)
  {
    client.appendBufferOut("ERROR :Invalid characters in username\r\n");
    return;
  }
  client.setUsername(arg[0]);
  client.setUserBool(true);
  if (client.getPassBool() && client.getNickBool())
    client.setAuth(true);
  return;
}

User::~User() {}
