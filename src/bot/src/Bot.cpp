#include "../include/Bot.hpp"
#include <iostream>
#include <stdio.h>

Bot::Bot() {}

// static std::string escapeJSON(const std::string &s)
// {
// 	std::string out;

// 	for (size_t i = 0; i < s.size(); i++)
// 	{
// 		if (s[i] == '"')
// 			out += "\\\"";
// 		else if (s[i] == '\\')
// 			out += "\\\\";
// 		else if (s[i] == '\n')
// 			out += "\\n";
// 		else
// 			out += s[i];
// 	}

// 	return out;
// }

// static std::string extractResponse(const std::string &json)
// {
// 	const std::string key = "\"response\":";
// 	size_t pos = json.find(key);
// 	if (pos == std::string::npos)
// 		return "";

// 	pos += key.length();

// 	// skip jusqu'à la première quote ouvrante
// 	while (pos < json.size() && json[pos] != '"')
// 		pos++;
// 	if (pos == json.size())
// 		return "";

// 	pos++; // après l’ouverture du guillemet
// 	std::string out;
// 	bool escape = false;

// 	for (; pos < json.size(); ++pos)
// 	{
// 		char c = json[pos];
// 		if (escape)
// 		{
// 			if (c == 'n')
// 				out += '\n';
// 			else if (c == 't')
// 				out += '\t';
// 			else if (c == 'r')
// 				out += '\r';
// 			else if (c == '\\' || c == '"')
// 				out += c;
// 			// on ignore les autres pour éviter erreurs
// 			escape = false;
// 		}
// 		else if (c == '\\')
// 		{
// 			escape = true;
// 		}
// 		else if (c == '"')
// 		{
// 			break; // fin de la chaîne
// 		}
// 		else
// 		{
// 			out += c;
// 		}
// 	}
// 	return out;
// }

std::string parseIRCRawMsg(const std::string rawMsg)
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
      std::cout << "[" << sender << "]" << std::endl;
    }
    else
      return "";
    size_t start = pos + 8;
    size_t end = rawMsg.find(" :", start);
    if (end != std::string::npos)
    {
      target = rawMsg.substr(start, end - start);
      std::cout << "[" << target << "]" << std::endl;
    }
    else
      return "";
    message = rawMsg.substr(end + 2);
    // if (message.length() > 2)
    // 	message.erase(message.length() - 2);
    std::cout << "[" << message << "]" << std::endl;
    return (message);
  }
  else
    return "";
}

// size_t i = 0;
// size_t pos = std::string::npos;

// if (rawMsg.size() > 0 && rawMsg[0] == ':')
// {
// 	i = rawMsg.find(' ');
// 	if (i == std::string::npos)
// 		return "";
// }

// pos = rawMsg.find(" :", i);

// if (pos == std::string::npos)
// 	return "";

// pos += 2; // skip " :"

// return rawMsg.substr(pos);

// std::string exec(const std::string &cmd)
// {
// 	char buffer[128];
// 	std::string result;

// 	FILE *pipe = popen(cmd.c_str(), "r");
// 	if (!pipe)
// 		return "error";

// 	while (fgets(buffer, sizeof(buffer), pipe))
// 		result += buffer;

// 	pclose(pipe);
// 	return result;
// }

std::string Bot::talk(const std::string &rawMsg)
{
  std::string msg = parseIRCRawMsg(rawMsg);
  std::cout << msg << std::endl;
  // std::string msg = escapeJSON(rawMsg);
  // std::cout << msg << std::endl;
  // std::ostringstream ss;
  // ss << "curl -s http://localhost:11434/api/generate "
  //    << "-H \"Content-Type: application/json\" "
  //    << "-d \"{"
  //    << "\\\"model\\\":\\\"monique\\\","
  //    << "\\\"prompt\\\":\\\"" << msg << "\\\","
  //    << "\\\"stream\\\":false"
  //    << "}\"";
  // //std::cout << ss.str() << std::endl;
  // std::string json = exec(ss.str());
  // //std::cout << json << std::endl;
  // extractResponse(json);
  return ("");
}

Bot::~Bot() {}
