#include "User.hpp"

User::User() {}

//TODO
// ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

static bool parsingUsername(std::string str)
{
  size_t i;
  const char badChar[] = {' ', '@', '!', '\0', '\r', '\n'};

  i = str.find_first_of(badChar, 0, 6);
  if (i != std::string::npos)
    return (false); //set BuffOut bad USERNAME
  return (true);
}

void User::execute(Client &client, ClientHandler &, ChannelHandler &, const std::vector<std::string> &arg)
{
  if (arg.size() > 4)
  {
    std::cout << "Missing arguments" << std::endl;
    return ;
  }
  if (parsingUsername(arg[0]) == false)
    return ;
  client.setUsername(arg[0]);
  client.setUserBool(true);
  return ;
}

User::~User(){}
