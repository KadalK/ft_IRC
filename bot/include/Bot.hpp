#pragma once
#include <string>
#include <vector>

class Bot
{
private:
  std::vector<std::string> _memories;
  Bot(const Bot &copy);
  Bot &operator=(const Bot &copy);

public:
  Bot();

  std::string talk(const std::string &input);
  ~Bot();
};
