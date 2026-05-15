#include "Utils.hpp"
#include <cstdlib>
#include <string>

bool isIntegerSign(const std::string &str)
{
  if ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))
    return (false);

  char *p;
  strtol(str.c_str(), &p, 10);

  if (*p == 0)
    return (true);
  return (false);
}

bool isInteger(const std::string &str)
{
  if ((!isdigit(str[0])))
    return (false);

  char *p;
  strtol(str.c_str(), &p, 10);

  if (*p == 0)
    return (true);
  return (false);
}

#define invalidChars " :,\r\n\t@!"

bool isValidKeyFormat(const std::string &key)
{
  if (key.size() > 23)
    return (false);
  size_t pos = key.find_first_of(invalidChars);
  if (pos != std::string::npos)
    return (false);
  return (true);
}
