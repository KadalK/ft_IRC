#pragma once

#include "ChannelHandler.hpp"
#include "ClientHandler.hpp"
#include "CommandsHandler.hpp"
#include <arpa/inet.h>
#include <csignal>
#include <cstdlib>
#include <fcntl.h>
#include <netinet/in.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

extern bool g_isRunning;

class Server
{

private:
  int _port;
  int _serverSocketFd;
  int _epollFd;
  std::string _time;

  std::vector<epoll_event> _events;
  std::string _password;

  ChannelHandler _channelHandler;
  ClientHandler _clientHandler;
  CommandsHandler _commandsHandler;

public:
  Server(int port, std::string password);

  void init();
  void run();
  void connectNewClient();
  void disconnectClient(int fd);
  void eventToServer(int fd);
  void setEpollOut(const std::vector<int> &vec);
  void eventToClient(int fd);

  ~Server();
};
