#include "Server.hpp"
#include "Utils.hpp"
#include <iostream>
#include <sstream>

bool g_isRunning = true;

void signal_handler(int signum)
{
  (void)signum;
  g_isRunning = false;
  std::cout << "\nThe server is closing..." << std::endl;
}

bool parseArgs(char *arg1, char *arg2)
{
  std::string portString = arg1;
  std::string password = arg2;
  if (portString.size() != 4 || !isInteger(portString))
  {
    std::cout << "Warning\nOnly 4 integers" << std::endl;
    return (false);
  }
  if (!isValidKeyFormat(password))
  {
    std::cout << "Warning\nUnvalid key format" << std::endl;
    return (false);
  }
  return (true);
}

int main(int argc, char **argv)
{
  if (argc != 3)
    return (1);
  signal(SIGINT, signal_handler);
  signal(SIGQUIT, signal_handler);
  if (!parseArgs(argv[1], argv[2]))
    return (1);
  std::stringstream ss(argv[1]);
  std::string password = argv[2];
  int port;
  ss >> port;
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
}
