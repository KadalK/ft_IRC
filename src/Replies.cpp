// #include "Replies.hpp"
#include <iostream>
#include <string>

// GLOBAL
// 401
const std::string ERR_NOSUCHNICK(const std::string &client,
                                 const std::string &nick)
{
  std::string out;

  out += client;
  out += " ";
  out += nick;
  out += " :No such nick/channel\r\n";
  return (out);
}
// 403
const std::string ERR_NOSUCHANNEL(const std::string &client,
                                  const std::string &channel)
{
  std::string out;

  out += client;
  out += " ";
  out += channel;
  out += " :No such nick/channel\r\n";
  return (out);
}

// 329
const std::string RPL_CREATIONTIME(const std::string &client,
                                   const std::string &channel,
                                   const std::string &creationTime)
{
  std::string out;

  out += ":server 329 ";
  out += client;
  out += " ";
  out += channel;
  out += " ";
  out += creationTime;
  out += "\r\n";

  return (out);
}

// 482
const std::string ERR_CHANNOPRIVSNEEDED(const std::string &client,
                                        const std::string &channel)
{
  std::string out;

  out += ":server 482 ";
  out += client;
  out += " ";
  out += channel;
  out += " :You're not channel operator\r\n";

  return (out);
}

// MODE
// NUMERIC  REPLIES
// 324
const std::string RPL_CHANNELMODEIS(const std::string &client,
                                    const std::string &channel,
                                    const std::string &modeString,
                                    const std::string &modeArguments)
{
  std::string out;

  out += ":server 324 ";
  out += client;
  out += " ";
  out += channel;
  out += " ";
  out += modeString;
  out += " ";
  out += modeArguments;
  out += "\r\n";

  return (out);
}
// 502
const std::string ERR_USERDONTMATCH(const std::string &client)
{
  std::string out;

  out += client;
  out += " :Cant change mode for other users";
  return (out);
}

// BROADCAST
const std::string Bc_Mode(const std::string)
