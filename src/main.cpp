#include <sstream>
#include "Server.hpp"
#include <iostream>
#include "Client.hpp"
#include "Channel.hpp"

<<<<<<< Updated upstream

bool g_isRunning = true;

void signal_handler(int signum)
{
    (void)signum;
	g_isRunning = false;
	std::cout << "\nThe server is closing..." << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return (1);
    signal(SIGINT,signal_handler);
    signal(SIGQUIT,signal_handler);
    // faire une verif sur le password et le port (au niveau du format)
    std::stringstream ss(argv[1]);
    int port;
    ss >> port;
    std::string password = argv[2];
    Server myServer(port, password);
    try
    {
        myServer.init();
        myServer.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return (1);
    }
    return 0;
=======
void parser(std::string rawMessage)
{

  PrivMsg p;
  Join j;
  Kick k;

  std::map<std::string, *Commands> commands = {{"PRIVMSG", p->execute()}, {"JOIN", j->execute()}}; //add toutes les commandes

  size_t pos;
  std::map<std::string, *Commands>::iterator i;

  pos = rawMessage.find(' ');
  if (pos == std::string::npos)
    return(-1); // throw exception
  if (rawMessage[pos] == ' ' && rawMessage[pos + 1] == ' ')
    return (-2);
  i = commands.find(rawMessage.substr(0, pos));
  if (i != commands.end())
    return (-3);
  std::cout << "Found : " << commands[i] << std::endl;
  return 0;

}

#include <iostream>
#include <map>
#include <algorithm>

int main()
{
  std::string rawMessage;
  rawMessage = "JOIN  kaan: salut";

  std::map<std::string, std::string> commands = {{"PRIVMSG", "PrivMsg"}, {"JOIN", "Join"}}; //add toutes les commandes

  size_t pos;
  std::map<std::string, std::string>::iterator i;

  pos = rawMessage.find(' ');
  if (pos == std::string::npos)
  {
    std::cout << "pas trouver despace" << std::endl;
    return(-1); // throw exception
  }
  if (rawMessage[pos] == ' ' && rawMessage[pos + 1] == ' ')
    return (-2);
  i = commands.find(rawMessage.substr(0, pos));
  if (i != commands.end())
    std::cout << "Found : " << i->second << std::endl;
  else
    return (-3);
  return 0;
>>>>>>> Stashed changes
}
