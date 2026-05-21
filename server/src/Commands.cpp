#include "Commands.hpp"

Commands::Commands() {}

Commands::~Commands() {}

std::vector<std::string> Commands::extractTokens(const std::string &str)
{
  std::vector<std::string> v;
  size_t start = 0;
  size_t pos;
  while ((pos = str.find(",", start)) != std::string::npos)
  {
    if (!str.substr(start, pos - start).empty())
      v.push_back(str.substr(start, pos - start));
    start = pos + 1;
  }
  if (!str.substr(start).empty())
    v.push_back(str.substr(start));
  return (v);
}
