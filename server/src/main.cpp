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

bool parseArgs(int port, std::string password)
{
  if (port > 65536 || port < 0)
  {
    std::cout << "Warning\nValid port input are between 1024 and 65536"
              << std::endl;
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
  std::stringstream ss(argv[1]);
  std::string password = argv[2];
  int port;
  ss >> port;
  if (!parseArgs(port, password))
    return (1);
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
