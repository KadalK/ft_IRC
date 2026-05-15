#include "commands/User.hpp"
#include "ChannelHandler.hpp"
#include "Client.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include "Replies.hpp"

User::User() {}

static bool parsingUsername(std::string str)
{
  size_t i;
  const char badChar[] = {' ', '@', '!', '\0', '\r', '\n'};

  i = str.find_first_of(badChar, 0, 6);
  if (i != std::string::npos)
    return (false); // set BuffOut bad USERNAME
  return (true);
}

void User::execute(Client &sender, ClientHandler &, ChannelHandler &,
                   const std::vector<std::string> &arg)
{
  if (arg.empty())
  {
    sender.appendBufferOut(
        Replies::ERR_NEEDMOREPARAMS(sender.getNickname(), "USER"));
    return;
  }
  if (sender.getUserBool())
  {
    sender.appendBufferOut(
        Replies::ERR_ALREADYREGISTERED(sender.getNickname()));
    return;
  }
  if (parsingUsername(arg[0]) == false)
  {
    sender.appendBufferOut("ERROR :Invalid characters in username\r\n");
    return;
  }
  sender.setUsername(arg[0]);
  sender.setUserBool(true);
  if (sender.getPassBool() && sender.getNickBool())
    sender.setAuth(true);
  return;
}

User::~User() {}
