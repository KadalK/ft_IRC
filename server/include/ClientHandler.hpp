#pragma once

#include <map>
#include <string>
#include <vector>

class Client;

class ClientHandler
{
private:
  std::map<int, Client *> _registry;

public:
  ClientHandler();
  ~ClientHandler();

  void addClient(int fd, std::string hostname, std::string time);
  void removeClient(int fd);

  Client *getClientByNickname(std::string nickname);
  std::vector<int> getAllFd();
  std::vector<int> getFdWithData();

  Client *getClientByFd(int fd);
};
