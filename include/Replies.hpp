#pragma once

#include <iostream>

class Replies
{
private:
  Replies();

public:
  /* WELCOME SUCCEFULL REGISTRATION
   * --------------------------------------------------------------*/

  // 001
  static const std::string RPL_WELCOME(const std::string &client,
                                       const std::string &nick);
  // 002
  static const std::string RPL_YOURHOST(const std::string &nick);
  // 003
  static const std::string RPL_CREATED(const std::string &nick,
                                       const std::string &time);
  // 004
  static const std::string RPL_MYINFO(const std::string &nick);

  /* GLOBAL --------------------------------------------------------------*/
  // 401
  static const std::string ERR_NOSUCHNICK(const std::string &client,
                                          const std::string &nick);
  // 403
  static const std::string ERR_NOSUCHANNEL(const std::string &client,
                                           const std::string &channel);
  // 329 L HEURE DE CREATION EST PAS FAITE
  static const std::string RPL_CREATIONTIME(const std::string &client,
                                            const std::string &channel,
                                            const std::string &creationTime);
  // 482
  static const std::string ERR_CHANNOPRIVSNEEDED(const std::string &client,
                                                 const std::string &channel);
  // 441
  static const std::string ERR_USERNOTINCHANNEL(const std::string &client,
                                                const std::string &nick,
                                                const std::string &channel);
  // 442
  static const std::string ERR_NOTONCHANNEL(const std::string &client,
                                            const std::string &channel);
  // 461
  static const std::string ERR_NEEDMOREPARAMS(const std::string &client,
                                              const std::string &command);

  // 462
  static const std::string ERR_ALREADYREGISTERED(const std::string &client);

  // 431
  static const std::string ERR_NONICKGIVEN(const std::string &nick);

   // 432
  static const std::string ERR_ERRONEUSNICKNAME (const std::string &nick, const std::string &new_nick);

  // 433
  static const std::string ERR_NICKNAMEINUSE (const std::string &nick, const std::string &new_nick);

   /* PASS ----------------------------------------------------------------*/
    // 324
  static const std::string ERR_PASSWDMISMATCH(const std::string &client);

  /* MODE ----------------------------------------------------------------*/
  // 324
  static const std::string RPL_CHANNELMODEIS(const std::string &client,
                                             const std::string &channel,
                                             const std::string &modeString);
  // 502
  static const std::string ERR_USERDONTMATCH(const std::string &client);

  // 467
  static const std::string ERR_KEYSET(const std::string &channel);

  // 472
  static const std::string ERR_UNKNOWNMODE(const std::string &client, char c);

  // 525
  static const std::string ERR_INVALIDKEY(const std::string &client,
                                          const std::string &channel);
  // BROADCAST
  static const std::string BC_MODE(const std::string &client,
                                   const std::string &channel,
                                   const std::string &modeString);
  /* INVITE --------------------------------------------------------------*/
  // 336
  static const std::string RPL_INVITELIST(const std::string &client,
                                          const std::string &channel);
  // 337
  static const std::string RPL_ENDOFINVITELIST(const std::string &client);
  // 341
  static const std::string RPL_INVITING(const std::string &client,
                                        const std::string &nick,
                                        const std::string &channel);
  // 443
  static const std::string ERR_USERONCHANNEL(const std::string &client,
                                             const std::string &nick,
                                             const std::string &channel);
  // BROADCAST
  static const std::string BC_INVITE(const std::string &client,
                                     const std::string &nick,
                                     const std::string &channel);

  /* INVITE --------------------------------------------------------------*/
  // BROADCAST
  static const std::string BC_KICK(const std::string &client,
                                   const std::string &nick,
                                   const std::string &channel,
                                   const std::string &comment);

  /* PRIVMSG --------------------------------------------------------------*/
  // 411
  static std::string ERR_NORECIPIENT(const std::string &server,
                                     const std::string &client,
                                     const std::string &command);
  // 412
  static std::string ERR_NOTEXTTOSEND(const std::string &server,
                                      const std::string &client);
  // 404
  static std::string ERR_CANNOTSENDTOCHAN(const std::string &server,
                                          const std::string &channel);
  // 414
  //  std::string ERR_WILDTOPLEVEL();
  // 407
  static std::string ERR_TOOMANYTARGETS(const std::string &server,
                                        const std::string &target,
                                        const std::string &abortMessage);
  // 301
  static std::string RPL_AWAY(const std::string &nick);

  /* JOIN --------------------------------------------------------------*/

  static const std::string RPL_JOIN(const std::string &client, const std::string& channel);
  // 331
  static const std::string RPL_NOTOPIC(const std::string &nick, const std::string &topic, const std::string &channel);
  // 332
  static const std::string RPL_TOPIC(const std::string &nick, const std::string &topic, const std::string &channel);
  // 353
  static const std::string RPL_NAMREPLY(const std::string &nick, const std::string &list, const std::string &channel);
  // 366
  static const std::string RPL_ENDOFNAMES(const std::string &nick, const std::string &channel);



  ~Replies();
};
