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

void Mode::execute(Client &client, ClientHandler &, ChannelHandler &chH,
                   const std::vector<std::string> &arg)
{
  Channel *channel;
  std::string flags;
  std::string param;
  std::vector<std::string>::const_iterator it;
  bool sign;
  size_t type;

  channel = chH.getChannelByName(arg[0]);
  if (!channel)
    return; // 403 "<client> <channel> :No such channel" D
  if (channel->isClientInChannel(client) == false)
    return;
  if (channel->isClientOperator(client) == false)
    return; // 482 "<client> <channel> :You're not channel operator" D
  if (arg.size() == 1)
  {
    std::cout << "modes are : hehehe" << std::endl;
    // 324 "<client> <channel> <modestring> <mode arguments>..." D
    // 329 "<client> <channel> <creationtime>" D
    return;
  }
  flags = arg[1];
  if (flags[0] != '-' && flags[0] != '+')
  {
    // 427 "<client> <modechar> :is unknown mode char to me" ND WTF ??
    return;
  }

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
    {
      // 427 "<client> <modechar> :is unknown mode char to me"
      std::cout << "wrong flag char : " << flags[i] << std::endl;
      return;
    }
    if (flags[i] == '+')
      sign = true;
    else if (flags[i] == '-')
      sign = false;
    else
    {
      if (((type == 'C' && sign == true) || type == 'B') && it != arg.end())
        param = *it++;
      else
        param = "";
      (channel->*channel->_modeFt[flags[i]])(sign, param, &client);
    }
  }
}

Mode::~Mode() {}
