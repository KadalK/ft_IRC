#include "../include/Bot.hpp"
#include "../../shared/Utils.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

int init(int port, std::string password)
{
  int botsocket = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in botAdress;
  botAdress.sin_family = AF_INET;
  botAdress.sin_port = htons(port);
  botAdress.sin_addr.s_addr = inet_addr("127.0.0.1");

  while (true)
  {
    if (connect(botsocket, (struct sockaddr *)&botAdress, sizeof(botAdress)) < 0)
    {
      std::cout << "Error : connect. New try in 3s...";
      sleep(3);
      continue;
    }
    break;
  }
  std::string WelcomePack =
      "PASS " + password + "\r\nNICK Monique\r\nUSER bot 0 * :IA\r\n";
  send(botsocket, WelcomePack.c_str(), WelcomePack.length(), 0);
  return (botsocket);
}

static bool parseArgs(char *arg1, char *arg2)
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

int main(int, char **argv)
{
  Bot bot;
  if (!parseArgs(argv[1], argv[2]))
    return (1);
  std::stringstream ss(argv[1]);
  std::string password = argv[2];
  int port;
  ss >> port;
  std::string format;
  int botfd = init(port, password);
  std::string readBuffer = "";
  while (true)
  {
    char temp[1024] = {0};
    int bytes = recv(botfd, temp, sizeof(temp) - 1, 0);
    if (bytes <= 0)
      break;
    readBuffer.append(temp, bytes);
    size_t pos;
    while ((pos = readBuffer.find("\r\n")) != std::string::npos)
    {
      std::string line = readBuffer.substr(0, pos);
      format = bot.talk(line);
      std::cout << "format : [" << format << "]" << std::endl;
      readBuffer.erase(0, pos + 2);
    }
    if (format != "")
    {
      send(botfd, format.c_str(), format.length(), 0);
      format.clear();
    }
  }
}
