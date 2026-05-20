#pragma once
#include <string>
#include <map>
#include <deque>
#include <vector>

struct ChatMessage {

  std::string role;
  std::string content;

};

class Bot
{
private:
  std::map<std::string, std::deque<ChatMessage> > _memory;
  size_t _memorySizeMax;
  Bot(const Bot &copy);
  Bot &operator=(const Bot &copy);

public:
  Bot();

  void        addMessageToMemory(const std::string& sender, const std::string& role, const std::string& content);
  std::string buildJson(const std::string& sender);
  std::string processUserInput(const std::string& sender, const std::string& userInput);
  std::string talk(const std::string &input);
  ~Bot();
};
