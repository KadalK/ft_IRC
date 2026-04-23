#include "Commands.hpp"
#include "PrivMsg.hpp"

PrivMsg::PrivMsg() {}
PrivMsg::PrivMsg(PrivMsg const &src) { (void)src; }
PrivMsg::~PrivMsg() {};
PrivMsg &PrivMsg::operator=(PrivMsg const &rhs) { (void)rhs; }

size_t PrivMsg::execute(std::string rawText, std::string sender)
{
  struct parameters p;

  if (this->parsingMessage(p, rawText) != 0)
    return (-1);//throw exception plus tard quoi en gros + errorMessage()
  
}

void parsingNickNames(parameters &p, std::string )

size_t PrivMsg::parsingMessage(parameters &p, std::string rawText)
{
  size_t pos = rawText.find(':');
  parsingNickNames(rawText.substr(0, pos));
  p.textMessage = rawText + pos;
}
