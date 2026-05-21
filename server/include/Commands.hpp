#pragma once

#include <string>
#include <vector>

class Client;
class ClientHandler;
class ChannelHandler;

class Commands
{
private:
  Commands(Commands const &src);
  Commands &operator=(Commands const &rhs);

protected:
public:
  Commands();
  virtual ~Commands();

  std::vector<std::string> extractTokens(const std::string &str);
  virtual void execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
                       const std::vector<std::string> &arg) = 0;
};
