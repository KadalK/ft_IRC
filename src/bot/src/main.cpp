#include "../include/Bot.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

int init()
{
  int botsocket = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in botAdress;
  botAdress.sin_family = AF_INET;
  botAdress.sin_port = htons(6667);
  botAdress.sin_addr.s_addr = inet_addr("127.0.0.1");

  while (true)
  {
    if (connect(botsocket, (struct sockaddr *)&botAdress, sizeof(botAdress)) <
        0)
    {
      std::cout << "Error : connect. New try in 3s...";
      sleep(3);
      continue;
    }
    break;
  }
  std::string WelcomePack = "PASS 123\r\nNICK Monique\r\nUSER bot 0 * :IA\r\n";
  send(botsocket, WelcomePack.c_str(), WelcomePack.length(), 0);
  std::cout << "je suis la lekip" << std::endl;
  return (botsocket);
}

// int main()
// {
//   Bot bot;
//   int botfd = init();
//   std::string readBuffer = "";
//   while (true)
//   {
//     char temp[1024] = {0};
//     int bytes = recv(botfd, temp, sizeof(temp) - 1, 0);
//     if (bytes <= 0)
//       break;
//     readBuffer.append(temp, bytes);
//     size_t pos;
//     while ((pos = readBuffer.find("\r\n")) != std::string::npos)
//     {
//       std::string line = readBuffer.substr(0, pos);
//       bot.talk(line);
//       readBuffer.erase(0, pos + 2);
//     }
//   }
//   // while (std::getline(std::cin, raw))
//   // {
//   // 	std::string response = bot.talk(raw);
//   // 	std::cout << "Monique: " << response << std::endl;
//   // }
//
//   return 0;
// }

int init(int port, std::string password)
{
  int botsocket = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in botAdress;
  botAdress.sin_family = AF_INET;
  botAdress.sin_port = htons(port);
  botAdress.sin_addr.s_addr = inet_addr("127.0.0.1");

  while (true)
  {
    if (connect(botsocket, (struct sockaddr *)&botAdress, sizeof(botAdress)) <
        0)
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

#include <sstream>

int main(int, char **argv)
{
  Bot bot;
  std::stringstream ss(argv[1]);
  std::cout << "port     : " << argv[1] << std::endl;
  std::cout << "password : " << argv[2] << std::endl;

  int port;
  ss >> port;
  std::string password = argv[2];
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
      bot.talk(line);
      readBuffer.erase(0, pos + 2);
    }
  }
  // while (std::getline(std::cin, raw))
  // {
  // 	std::string response = bot.talk(raw);
  // 	std::cout << "Monique: " << response << std::endl;
  // }

  return 0;
}
