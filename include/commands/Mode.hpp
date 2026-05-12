#pragma once

#include "Commands.hpp"
#include "Replies.hpp"

class Mode : public Commands
{
private:
  Mode(Mode const &src);
  Mode &operator=(Mode const &rhs);

public:
  Mode();

  // void parsingMessage(std::string rawText);
  void execute(Client &client, ClientHandler &clH, ChannelHandler &chH,
               const std::vector<std::string> &arg);
  void errorMessage(size_t errorValue);
  ~Mode();
};
