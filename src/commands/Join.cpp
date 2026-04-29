#include "commands/Join.hpp"

Join::Join(){}

std::vector<std::string> extractTokens(const std::string &str)
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

void Join::execute(Client& client, ClientHandler &, ChannelHandler &chH, const std::vector<std::string>& arg)
{
  std::vector<std::string> channels;
  std::vector <std::string> passwords;
  std::vector<std::string>::iterator pIt;
  std::string inPassword;

  if (arg.empty() == true)
  {
    std::cout << "Missing arguments" << std::endl;
    return ;
  }
  channels = extractTokens(arg[0]);
  if (arg.size() > 1 && arg[1].empty() == false)
    passwords = extractTokens(arg[1]);
  pIt = passwords.begin();
  for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
  {
    if (pIt != passwords.end())
    {
      inPassword = *pIt;
      pIt++;
    }
    else
      inPassword = "";
    if ((*it)[0] != '#')
       std::cout << *it << " :No such channel" << std::endl;
    else
    {
      Channel *chToJoin = chH.getChannelByName(*it);
      if (chToJoin == NULL)
      {
        chH.createChannel(*it, &client);
        client.appendBufferOut("Created channel connard\n");
        std::cout << "Created channel " << chH.getChannelByName(*it)->getName() << std::endl;
      }
      else
      {
        if (chToJoin->canJoinChannel(client, inPassword) == true)
        {
          std::cout << "avant addclient " << &client << std::endl;
          chToJoin->addClient(&client);
          // client.appendBufferOut("Joined channel connard\n");
          // std::cout << "Joined channel " << chToJoin->getName() << std::endl;
        }
        // Suppose to send confirmation message + all mode to client that joined.
        // + msg to all channel member to notify newcomer
      }
    }
  }
}

Join::~Join(){}
