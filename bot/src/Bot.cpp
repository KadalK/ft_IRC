#include "Bot.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>

Bot::Bot() { this->_memorySizeMax = 20; }

static std::string escapeJSON(const std::string &s)
{
  std::string out;

  for (size_t i = 0; i < s.size(); i++)
  {
    if (s[i] == '"')
      out += "\\\\\\\"";
    else if (s[i] == '\\')
      out += "\\\\\\\\";
    else if (s[i] == '\n')
      out += "\\n";
    else
      out += s[i];
  }

  return out;
}

std::string exec(const std::string &cmd)
{
  char buffer[128];
  std::string result;

  FILE *pipe = popen(cmd.c_str(), "r");
  if (!pipe)
    return "error";

  while (fgets(buffer, sizeof(buffer), pipe))
    result += buffer;

  pclose(pipe);
  return result;
}

static std::string extractResponse(const std::string &json)
{
  const std::string key = "\"content\":";
  size_t pos = json.find(key);
  if (pos == std::string::npos)
    return "";
  pos += key.length();
  while (pos < json.size() && json[pos] != '"')
    pos++;
  if (pos == json.size())
    return "";
  pos++;
  std::string out;
  bool escape = false;
  for (; pos < json.size(); ++pos)
  {
    char c = json[pos];
    if (escape)
    {
      if (c == 'n')
        out += ' ';
      else if (c == 't')
        out += ' ';
      else if (c == 'r')
        out += ' ';
      else if (c == '\\' || c == '"')
        out += c;

      escape = false;
    }
    else if (c == '\\')
      escape = true;
    else if (c == '"')
      break;
    else
      out += c;
  }
  return out;
}

void Bot::addMessageToMemory(const std::string &sender, const std::string &role,
                             const std::string &content)
{
  ChatMessage msg;
  msg.role = role;
  msg.content = content;
  _memory[sender].push_back(msg);
  while (_memory[sender].size() > this->_memorySizeMax)
    _memory[sender].pop_front();
}

std::string Bot::buildJson(const std::string &sender)
{
  std::stringstream ss;

  ss << "{"
     << "\\\"model\\\": \\\"monique\\\", "
     << "\\\"stream\\\": false, "
     << "\\\"messages\\\": [";
  std::deque<ChatMessage> &history = _memory[sender];
  for (size_t i = 0; i < history.size(); ++i)
  {
    std::string cleanContent = escapeJSON(history[i].content);
    std::cout << " buildJson history[i].role [" << history[i].role << "]"
              << std::endl;
    std::cout << " buildJson cleancontent [" << cleanContent << "]"
              << std::endl;
    ss << "{"
       << "\\\"role\\\": \\\"" << history[i].role << "\\\", "
       << "\\\"content\\\": \\\"" << cleanContent << "\\\""
       << "}";

    if (i < history.size() - 1)
      ss << ", ";
  }
  ss << "]}";
  return ss.str();
}

std::string Bot::processUserInput(const std::string &sender,
                                  const std::string &userInput)
{
  addMessageToMemory(sender, "user", userInput);
  std::string json = buildJson(sender);
  std::string cmd = "curl -s http://localhost:11434/api/chat "
                    "-H \"Content-Type: application/json\" "
                    "-d \"" +
                    json + "\"";
  std::string rawResponse = exec(cmd);
  std::cout << "rawResponse : [" << rawResponse << "]" << std::endl;
  std::string botReply = extractResponse(rawResponse);
  std::cout << "botReply : [" << botReply << "]" << std::endl;
  if (!botReply.empty())
    addMessageToMemory(sender, "assistant", botReply);
  return (botReply);
}

std::string parseBotReply(std::string &reply, std::string sender)
{
  std::string ircReply = "";
  size_t max_len = 400;
  size_t i = 0;
  while (i < reply.length())
  {
    size_t chunk_size = max_len;
    if (i + chunk_size < reply.length())
    {
      size_t last_space = reply.rfind(' ', i + chunk_size);
      if (last_space != std::string::npos && last_space > i)
        chunk_size = last_space - i;
    }
    else
      chunk_size = reply.length() - i;
    std::string chunk = reply.substr(i, chunk_size);
    ircReply += "PRIVMSG " + sender + " :" + chunk + "\r\n";
    i += chunk_size;
    while (i < reply.length() && reply[i] == ' ')
      i++;
  }
  return (ircReply);
}

std::string Bot::talk(const std::string &rawMsg)
{

  std::string sender;
  std::string target;
  std::string message;

  size_t pos;
  if ((pos = rawMsg.find("PRIVMSG")) != std::string::npos)
  {
    size_t tpos = rawMsg.find("!");
    if (tpos != std::string::npos)
    {
      sender = rawMsg.substr(1, tpos - 1);
      std::cout << "sender : [" << sender << "]" << std::endl;
    }
    else
      return "";
    size_t start = pos + 8;
    size_t end = rawMsg.find(" :", start);
    if (end != std::string::npos)
    {
      target = rawMsg.substr(start, end - start);
      std::cout << "target : [" << target << "]" << std::endl;
    }
    else
      return "";
    message = rawMsg.substr(end + 2);
    std::cout << "message : [" << message << "]" << std::endl;
  }
  else
    message = "";
  if (!message.empty())
  {
    std::string reply = processUserInput(sender, message);
    return (parseBotReply(reply, sender));
  }
  return (message);
}

Bot::~Bot() {}
