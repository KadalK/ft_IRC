#include "Replies.hpp"
#include <string>

/* WELCOME SUCCEFULL REGISTRATION
 * --------------------------------------------------------------*/
// 001
const std::string Replies::RPL_WELCOME(const std::string &nick,
                                       const std::string &fullname)
{
  std::string out = "";

  out += ":ircserv 001 ";
  out += fullname;
  out += " :Welcome to the Internet Relay Network ";
  out += nick;
  out += "\r\n";

  return (out);
}

// 002
const std::string Replies::RPL_YOURHOST(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 002 ";
  out += nick;
  out += " :Your host is ircserv, running version 1.0\r\n";

  return (out);
}

// 003
const std::string Replies::RPL_CREATED(const std::string &nick,
                                       const std::string &time)
{
  std::string out = "";

  out += ":ircserv 003 ";
  out += nick;
  out += " :This server was created ";
  out += time;
  out += "\r\n";

  return (out);
}

const std::string Replies::RPL_MYINFO(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 004 ";
  out += nick;
  out += " ircserv 1.0 o itkol\r\n";

  return (out);
}

// 005
const std::string Replies::RPL_ISUPPORT(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 005 ";
  out += nick;
  out += " CHANTYPES=# PREFIX=(o)@ MODES=5 TARGMAX=PRIVMSG:4,KICK:4 :Are "
         "supported by this server\r\n";

  return (out);
}

// 421
const std::string Replies::ERR_UNKNOWNCOMMAND(const std::string &nick,
                                              const std::string &command)
{
  std::string out = "";

  out += ":ircserv 421 ";
  out += nick;
  out += " ";
  out += command;
  out += " :Unknown command\r\n";

  return (out);
}
/* GLOBAL --------------------------------------------------------------*/
// 329
const std::string Replies::RPL_CREATIONTIME(const std::string &nick,
                                            const std::string &channel,
                                            const std::string &creationTime)
{
  std::string out = "";

  out += ":ircserv 329 ";
  out += nick;
  out += " ";
  out += channel;
  out += " ";
  out += creationTime;
  out += "\r\n";

  return (out);
}



// 401
const std::string Replies::ERR_NOSUCHNICK(const std::string &nick,
                                          const std::string &input)
{
  std::string out = "";

  out += ":ircserv 401 ";
  out += nick;
  out += " ";
  out += input;
  out += " :No such nick/channel\r\n";

  return (out);
}
// 403
const std::string Replies::ERR_NOSUCHANNEL(const std::string &nick,
                                           const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 403 ";
  out += nick;
  out += " ";
  out += channel;
  out += " :No such channel\r\n";

  return (out);
}

// 431
const std::string Replies::ERR_NONICKGIVEN(const std::string &nick)
{
  std::string out = ":ircserv 431 ";

  out += nick;
  out += " :No nickname given\r\n";

  return (out);
}

// 432
const std::string Replies::ERR_ERRONEUSNICKNAME(const std::string &nick,
                                                const std::string &newnick)
{
  std::string out = "";

  out += ":ircserv 432 ";
  out += nick;
  out += " ";
  out += newnick;
  out += " :Erroneous nickname\r\n";

  return (out);
}

// 433
const std::string Replies::ERR_NICKNAMEINUSE(const std::string &nick,
                                             const std::string &newnick)
{
  std::string out = "";

  out += ":ircserv 433 ";
  out += nick;
  out += " ";
  out += newnick;
  out += " :Nickname is already in use\r\n";

  return (out);
}

// 441
const std::string Replies::ERR_USERNOTINCHANNEL(const std::string &nick,
                                                const std::string &input,
                                                const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 441 ";
  out += nick;
  out += " ";
  out += input;
  out += " ";
  out += channel;
  out += " :They aren't on that channel\r\n";

  return (out);
}

// 442
const std::string Replies::ERR_NOTONCHANNEL(const std::string &nick,
                                            const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 442 ";
  out += nick;
  out += " ";
  out += channel;
  out += " :You're not on that channel\r\n";

  return (out);
}

// 451
const std::string Replies::ERR_NOTREGISTERED(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 451 ";
  out += nick;
  out += " :You have not registered\r\n";

  return (out);
}

// 461
const std::string Replies::ERR_NEEDMOREPARAMS(const std::string &nick,
                                              const std::string &command)
{
  std::string out = "";

  out += ":ircserv 461 ";
  out += nick;
  out += " ";
  out += command;
  out += " :Not enough parameters\r\n";

  return (out);
}

// 462
const std::string Replies::ERR_ALREADYREGISTERED(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 462 ";
  out += nick;
  out += " :Unauthorized command (already registered)\r\n";

  return (out);
}

// 482
const std::string Replies::ERR_CHANNOPRIVSNEEDED(const std::string &nick,
                                                 const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 482 ";
  out += nick;
  out += " ";
  out += channel;
  out += " :You're not channel operator\r\n";

  return (out);
}

// FT01 BAD_PREFIX
const std::string Replies::ERR_BADPREFIX(const std::string &nick)
{
  std::string out = "";

  out += ":FT01 ";
  out += nick;
  out += " :Unvalid prefix\r\n";

  return (out);
}

/* PASS --------------------------------------------------------------*/
// 464
const std::string Replies::ERR_PASSWDMISMATCH(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 464 ";
  out += nick;
  out += " :Password incorrect\r\n";

  return (out);
}

/* NICK --------------------------------------------------------------*/
// BROADCAST
const std::string Replies::BC_NICK(const std::string &sender,
                                   const std::string &newnick)
{
  std::string out = "";

  out += sender;
  out += " NICK ";
  out += newnick;
  out += "\r\n";

  return (out);
}

/* MODE --------------------------------------------------------------*/
// 324
const std::string Replies::RPL_CHANNELMODEIS(const std::string &nick,
                                             const std::string &channel,
                                             const std::string &modeString)
{
  std::string out = "";

  out += ":ircserv 324 ";
  out += nick;
  out += " ";
  out += channel;
  out += " ";
  out += modeString;
  out += "\r\n";

  return (out);
}

// 467
const std::string Replies::ERR_KEYSET(const std::string &nick,
                                      const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 467 ";
  out += nick;
  out += " ";
  out += channel;
  out += " :Channel key already set";
  out += "\r\n";

  return (out);
}

// 472
const std::string Replies::ERR_UNKNOWNMODE(const std::string &nick, char c)
{
  std::string out = "";

  out += ":ircserv 472 ";
  out += nick;
  out += " ";
  out += c;
  out += "\r\n";

  return (out);
}

// 502
const std::string Replies::ERR_USERDONTMATCH(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 502 ";
  out += nick;
  out += " :Can't change mode for other users";
  out += "\r\n";

  return (out);
}

// 525
const std::string Replies::ERR_INVALIDKEY(const std::string &nick,
                                          const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 525 ";
  out += nick;
  out += " ";
  out += channel;
  out += " :Key is not well formed\r\n";

  return (out);
}

// BROADCAST
const std::string Replies::BC_MODE(const std::string &sender,
                                   const std::string &channel,
                                   const std::string &modeString)
{
  std::string out = "";

  out += sender;
  out += " MODE ";
  out += channel;
  out += " ";
  out += modeString;
  out += "\r\n";

  return (out);
}

/* WHO  --------------------------------------------------------------*/
  // 352
  const std::string Replies::RPL_WHOREPLY(const std::string &nick,const std::string &fullInfo)
  {
    std::string out = "";

    out += ":ircserv 352 ";
    out += nick;
    out += " ";
    out += fullInfo;
    out += "\r\n";

    return (out);
  }

  // 315
  const std::string Replies::RPL_ENDOFWHO(const std::string &nick,const std::string &name)
  {
    std::string out = "";

    out += ":ircserv 315 ";
    out += nick + " ";
    out += name;
    out += " :End of WHO list\r\n";

    return (out);

  }

/* AWAY  --------------------------------------------------------------*/
// 306
const std::string Replies::RPL_NOWAWAY(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 306 ";
  out += nick;
  out += " :You have been marked as being away";
  out += "\r\n";

  return (out);
}

// 305
// const std::string Replies::BC_NOWAWAY(const std::string &nick, const std::string &awayMsg)
// {
//   std::string out = "";

//   out += ":ircserv 306 ";
//   out += nick;
//   out += " :";
//   out += nick;
//   out += " has been marked as being away because ";
//   out += awayMsg;
//   out += "\r\n";

//   return (out);
// }

// 305
const std::string Replies::BC_NOWAWAY(const std::string &sender , const std::string &awayMsg)
{
  std::string out = "";

  out += sender;
  out += " AWAY ";
  out += ": has been marked as being away ";
  out += awayMsg;
  out += "\r\n";

  return (out);
}


// 305
const std::string Replies::BC_UNAWAY(const std::string &sender)
{
  std::string out = "";

  out += sender;
  out += " BACK ";
  out += ": are no longer marked as being away";
  out += "\r\n";

  return (out);
}

// 305
const std::string Replies::RPL_UNAWAY(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 305 ";
  out += nick;
  out += " :You are no longer marked as being away";
  out += "\r\n";

  return (out);
}

// 301
const std::string Replies::RPL_AWAY(const std::string &nick, const std::string &sender,const std::string &awayMsg)
{
  std::string out = "";

  out += ":ircserv 301 ";
  out += sender;
  out += " ";
  out += nick;
  out += " :";
  out += awayMsg;
  out += "\r\n";

  return (out);
}

/* INVITE  --------------------------------------------------------------*/
// 336
const std::string Replies::RPL_INVITELIST(const std::string &nick,
                                          const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 336 ";
  out += nick;
  out += " ";
  out += channel;
  out += "\r\n";

  return (out);
}

// 337
const std::string Replies::RPL_ENDOFINVITELIST(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 337 ";
  out += nick;
  out += " :End of /INVITE list";
  out += "\r\n";

  return (out);
}

// 341
const std::string Replies::RPL_INVITING(const std::string &nick,
                                        const std::string &input,
                                        const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 341 ";
  out += nick;
  out += " ";
  out += input;
  out += " ";
  out += channel;
  out += "\r\n";

  return (out);
}

// 443
const std::string Replies::ERR_USERONCHANNEL(const std::string &nick,
                                             const std::string &input,
                                             const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 443 ";
  out += nick;
  out += " ";
  out += input;
  out += " ";
  out += channel;
  out += " :is already on channel";
  out += "\r\n";

  return (out);
}

// BROADCAST
const std::string Replies::BC_INVITE(const std::string &sender,
                                     const std::string &channel,
                                     const std::string &nick)
{
  std::string out = "";

  out += sender;
  out += " INVITE ";
  out += channel;
  out += " ";
  out += nick;
  out += "\r\n";

  return (out);
}
/* KICK -----------------------------------------------------------------*/
// BROADCAST
const std::string Replies::BC_KICK(const std::string &sender,
                                   const std::string &nick,
                                   const std::string &channel,
                                   const std::string &comment)
{
  std::string out = "";

  out += sender;
  out += " KICK ";
  out += channel;
  out += " ";
  out += nick;
  out += " :" + comment;
  out += "\r\n";

  return (out);
}

/* PART -----------------------------------------------------------------*/
// BROADCAST
const std::string Replies::BC_PART(const std::string &sender,
                                   const std::string &channel,
                                   const std::string &comment)
{
  std::string out = "";

  out += sender;
  out += " PART ";
  out += channel;
  if (comment != "")
    out += " :" + comment;
  out += "\r\n";

  return (out);
}

/* TOPIC -----------------------------------------------------------------*/
// 331
const std::string Replies::RPL_NOTOPIC(const std::string &nick,
                                       const std::string &topic,
                                       const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 331 ";
  out += nick;
  out += " ";
  out += channel;
  out += " :";
  out += topic;
  out += "\r\n";

  return (out);
}

// 332
const std::string Replies::RPL_TOPIC(const std::string &nick,
                                     const std::string &topic,
                                     const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 332 ";
  out += nick;
  out += " ";
  out += channel;
  out += " :";
  out += topic;
  out += "\r\n";

  return (out);
}

// BROADCAST
const std::string Replies::BC_TOPIC(const std::string &sender,
                                    const std::string &channel,
                                    const std::string &comment)
{
  std::string out = "";

  out += sender;
  out += " TOPIC ";
  out += channel;
  out += " :" + comment;
  out += "\r\n";

  return (out);
}

/* PRIVMSG --------------------------------------------------------------*/
// 407
const std::string Replies::ERR_TOOMANYTARGETS(const std::string &target,
                                              const std::string &targetsCount)
{
  std::string out;

  out += ":ircserv 407 ";
  out += target;
  out += " :";
  out += targetsCount;
  out += " Message delivery aborted\r\n";

  return (out);
}

// 411
const std::string Replies::ERR_NORECIPIENT(const std::string &nick,
                                           const std::string &command)
{
  std::string out;

  out += ":ircserv 411 ";
  out += nick;
  out += " :No recipient given (";
  out += command;
  out += ")\r\n";

  return (out);
}

// 412
const std::string Replies::ERR_NOTEXTTOSEND(const std::string &nick)
{
  std::string out;

  out += ":ircserv 412 ";
  out += nick;
  out += " :No text to send\r\n";

  return (out);
}

// BROADCAST
const std::string Replies::BC_PRIVMSG(const std::string &sender,
                                      const std::string &target,
                                      const std::string &msg)
{
  std::string out = "";

  out += sender;
  out += " PRIVMSG ";
  out += target;
  out += " :";
  out += msg;
  out += "\r\n";

  return (out);
}
/* JOIN --------------------------------------------------------------*/
// 471
const std::string Replies::ERR_CHANNELISFULL(const std::string &nick,
                                             const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 471 ";
  out += nick;
  out += " ";
  out += channel;
  out += ":Cannot join channel (+l)\r\n";

  return (out);
}

// 473
const std::string Replies::ERR_INVITEONLYCHAN(const std::string &nick,
                                              const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 473 ";
  out += nick;
  out += " ";
  out += channel;
  out += ":Cannot join channel (+i)\r\n";

  return (out);
}

// 475
const std::string Replies::ERR_BADCHANNELKEY(const std::string &nick,
                                             const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 475 ";
  out += nick;
  out += " ";
  out += channel;
  out += ":Cannot join channel (+k)\r\n";

  return (out);
}

// BROADCAST
const std::string Replies::BC_JOIN(const std::string &sender,
                                   const std::string &channel)
{
  std::string out = "";

  out += sender;
  out += " JOIN";
  out += " :" + channel;
  out += "\r\n";

  return (out);
}

/* NAMES --------------------------------------------------------------*/
// 353
const std::string Replies::RPL_NAMREPLY(const std::string &nick,
                                        const std::string &list,
                                        const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 353 ";
  out += nick;
  out += " = ";
  out += channel;
  out += " :";
  out += list;
  out += "\r\n";

  return (out);
}

// 366
const std::string Replies::RPL_ENDOFNAMES(const std::string &nick,
                                          const std::string &channel)
{
  std::string out = "";

  out += ":ircserv 366 ";
  out += nick;
  out += " ";
  out += channel;
  out += " :End of /NAMES list\r\n";

  return (out);
}

/* LIST --------------------------------------------------------------*/
// 321 -- OLD RFC. May be needed for old IRC client
// const std::string Replies::RPL_LISTSTART(const std::string &nick)
// {
//   std::string out = "";
//
//   out += ":ircserv 321 ";
//   out += nick;
//   out += " Channel :Users Name\r\n";
//
//   return (out);
// }

// 322
const std::string Replies::RPL_LIST(const std::string &nick,
                                    const std::string &channel,
                                    const std::string &count,
                                    const std::string &topic)
{
  std::string out = "";

  out += ":ircserv 322 ";
  out += nick;
  out += " ";
  out += channel;
  out += " ";
  out += count;
  out += " :" + topic;
  out += "\r\n";

  return (out);
}

// 323
const std::string Replies::RPL_LISTEND(const std::string &nick)
{
  std::string out = "";

  out += ":ircserv 323 ";
  out += nick;
  out += " :End of /LIST\r\n";

  return (out);
}
