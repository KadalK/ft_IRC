#include "Replies.hpp"
#include <iostream>
#include <string>

/* GLOBAL --------------------------------------------------------------*/
// 401
const std::string Replies::ERR_NOSUCHNICK(const std::string &client,
                                          const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 401 ";
  out += client;
  out += " ";
  out += nick;
  out += " :No such nick\r\n";

  return (out);
}
// 403
const std::string Replies::ERR_NOSUCHANNEL(const std::string &client,
                                           const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 403 ";
  out += client;
  out += " ";
  out += channel;
  out += " :No such channel\r\n";

  return (out);
}

// 329
const std::string Replies::RPL_CREATIONTIME(const std::string &client,
                                            const std::string &channel,
                                            const std::string &creationTime)
{
  std::string out = "";

  out += ":ircserv 329 ";
  out += client;
  out += " ";
  out += channel;
  out += " ";
  out += creationTime;
  out += "\r\n";

  return (out);
}

// 441
const std::string Replies::ERR_USERNOTINCHANNEL(const std::string &client,
                                                const std::string &nick,
                                                const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 441 ";
  out += client;
  out += " ";
  out += nick;
  out += " ";
  out += channel;
  out += " :They aren't on that channel\r\n";

  return (out);
}

// 442
const std::string Replies::ERR_NOTONCHANNEL(const std::string &client,
                                            const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 442 ";
  out += client;
  out += " ";
  out += channel;
  out += " :You're not on that channel\r\n";

  return (out);
}

// 461
const std::string Replies::ERR_NEEDMOREPARAMS(const std::string &client,
                                              const std::string &command)
{
  std::string out = "";

  out += ":ircserv 461 ";
  out += client;
  out += " ";
  out += command;
  out += " :Not enough parameters\r\n";

  return (out);
}

// 482
const std::string Replies::ERR_CHANNOPRIVSNEEDED(const std::string &client,
                                                 const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 482 ";
  out += client;
  out += " ";
  out += channel;
  out += " :You're not channel operator\r\n";

  return (out);
}

/* MODE --------------------------------------------------------------*/
// NUMERIC  REPLIES
// 324
const std::string Replies::RPL_CHANNELMODEIS(const std::string &client,
                                             const std::string &channel,
                                             const std::string &modeString)
{
  std::string out = "";

  out += ":ircserv 324 ";
  out += client;
  out += " ";
  out += channel;
  out += " ";
  out += modeString;
  out += "\r\n";

  return (out);
}
// 502
const std::string Replies::ERR_USERDONTMATCH(const std::string &client)
{
  std::string out = "";

  out += ":ircserv 502 ";
  out += client;
  out += " :Can't change mode for other users";
  out += "\r\n";

  return (out);
}

// 467
const std::string Replies::ERR_KEYSET(const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 467 ";
  out += channel;
  out += " :Channel key already set";
  out += "\r\n";

  return (out);
}

// 472
const std::string Replies::ERR_UNKNOWNMODE(const std::string &client, char c)
{
  std::string out = "";

  out += ":ircserv 472 ";
  out += client;
  out += " ";
  out += c;
  out += "\r\n";

  return (out);
}

// 525
const std::string Replies::ERR_INVALIDKEY(const std::string &client,
                                          const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 525 ";
  out += client;
  out += " ";
  out += channel;
  out += " :Key is not well formed\r\n";

  return (out);
}

// BROADCAST
const std::string Replies::BC_MODE(const std::string &client,
                                   const std::string &channel,
                                   const std::string &modeString)
{
  std::string out = "";

  out += ":" + client;
  out += " MODE ";
  out += channel;
  out += " ";
  out += modeString;
  out += "\r\n";

  return (out);
}
/* INVITE  --------------------------------------------------------------*/
// 336
const std::string Replies::RPL_INVITELIST(const std::string &client,
                                          const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 336 ";
  out += client;
  out += " ";
  out += channel;
  out += "\r\n";

  return (out);
}

// 337
const std::string Replies::RPL_ENDOFINVITELIST(const std::string &client)
{
  std::string out = "";

  out += ":ircserv 337 ";
  out += client;
  out += " :End of /INVITE list";
  out += "\r\n";

  return (out);
}

// 341
const std::string Replies::RPL_INVITING(const std::string &client,
                                        const std::string &nick,
                                        const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 341 ";
  out += client;
  out += " ";
  out += nick;
  out += " ";
  out += channel;
  out += "\r\n";

  return (out);
}

// 443
const std::string Replies::ERR_USERONCHANNEL(const std::string &client,
                                             const std::string &nick,
                                             const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 443 ";
  out += client;
  out += " ";
  out += nick;
  out += " ";
  out += channel;
  out += ":is already on channel";
  out += "\r\n";

  return (out);
}

// BROADCAST
const std::string Replies::BC_INVITE(const std::string &client,
                                     const std::string &channel)
{

  std::string out = "";

  out += ":" + client;
  out += " INVITE ";
  out += channel;
  out += "\r\n";

  return (out);
}
/* PRIVMSG --------------------------------------------------------------*/
// 411
std::string Replies::ERR_NORECIPIENT(const std::string &ircserv,
                                     const std::string &client,
                                     const std::string &command)
{
  return (":" + ircserv + " 411 " + client + " :No recipient given (" +
          command + ")\r\n");
}

// 412
std::string Replies::ERR_NOTEXTTOSEND(const std::string &ircserv,
                                      const std::string &client)
{
  return (":" + ircserv + " 412 " + client + " :No text to send\r\n");
}

// 404
std::string Replies::ERR_CANNOTSENDTOCHAN(const std::string &ircserv,
                                          const std::string &channel)
{
  return (":" + ircserv + " 404 " + channel + " :Cannot send to channel\r\n");
}

// 414
//  std::string Replies::ERR_WILDTOPLEVEL(){}

// 407
std::string Replies::ERR_TOOMANYTARGETS(const std::string &ircserv,
                                        const std::string &target,
                                        const std::string &abortMessage)
{
  return (":" + ircserv + " 407 " + target + " :407 recipients. " +
          abortMessage + "\r\n");
}

// // 301
// std::string Replies::RPL_AWAY(const std::string &ircserv,
//                               const std::string &nick,
//                               const std::string &awayMsg)
// {
//   return (":" + ircserv + " 301 " + nick + " :" + awayMsg + "\r\n");
// }
