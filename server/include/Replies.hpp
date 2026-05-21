#pragma once

#include <string>

class Replies
{
private:
  Replies();

public:
  /* WELCOME SUCCESSFULL REGISTRATION
   * --------------------------------------------------------------*/
  // 001
  static const std::string RPL_WELCOME(const std::string &nick,
                                       const std::string &input);
  // 002
  static const std::string RPL_YOURHOST(const std::string &nick);

  // 003
  static const std::string RPL_CREATED(const std::string &nick,
                                       const std::string &time);
  // 004
  static const std::string RPL_MYINFO(const std::string &nick);

  // 005
  static const std::string RPL_ISUPPORT(const std::string &nick);

  // 421
  static const std::string ERR_UNKNOWNCOMMAND(const std::string &nick,
                                              const std::string &command);
  /* GLOBAL --------------------------------------------------------------*/
  // 401
  static const std::string ERR_NOSUCHNICK(const std::string &nick,
                                          const std::string &input);
  // 403
  static const std::string ERR_NOSUCHANNEL(const std::string &nick,
                                           const std::string &channel);
  // 329
  static const std::string RPL_CREATIONTIME(const std::string &nick,
                                            const std::string &channel,
                                            const std::string &creationTime);
  // 431
  static const std::string ERR_NONICKGIVEN(const std::string &nick);

  // 432
  static const std::string ERR_ERRONEUSNICKNAME(const std::string &nick,
                                                const std::string &new_nick);
  // 433
  static const std::string ERR_NICKNAMEINUSE(const std::string &nick,
                                             const std::string &new_nick);
  // 441
  static const std::string ERR_USERNOTINCHANNEL(const std::string &nick,
                                                const std::string &input,
                                                const std::string &channel);
  // 442
  static const std::string ERR_NOTONCHANNEL(const std::string &nick,
                                            const std::string &channel);
  // 451
  static const std::string ERR_NOTREGISTERED(const std::string &nick);

  // 461
  static const std::string ERR_NEEDMOREPARAMS(const std::string &nick,
                                              const std::string &command);
  // 462
  static const std::string ERR_ALREADYREGISTERED(const std::string &nick);

  // 482
  static const std::string ERR_CHANNOPRIVSNEEDED(const std::string &nick,
                                                 const std::string &channel);

  // FT01 BAD PREFIX
  static const std::string ERR_BADPREFIX(const std::string &nick);

  /* PASS ----------------------------------------------------------------*/
  // 324
  static const std::string ERR_PASSWDMISMATCH(const std::string &nick);

  /* MODE ----------------------------------------------------------------*/
  // 324
  static const std::string RPL_CHANNELMODEIS(const std::string &nick,
                                             const std::string &channel,
                                             const std::string &modeString);
  // 467
  static const std::string ERR_KEYSET(const std::string &nick,
                                      const std::string &channel);
  // 472
  static const std::string ERR_UNKNOWNMODE(const std::string &nick, char c);
  // 502
  static const std::string ERR_USERDONTMATCH(const std::string &nick);
  // 525
  static const std::string ERR_INVALIDKEY(const std::string &nick,
                                          const std::string &channel);
  // BROADCAST
  static const std::string BC_MODE(const std::string &sender,
                                   const std::string &channel,
                                   const std::string &modeString);
  /* INVITE --------------------------------------------------------------*/
  // 336
  static const std::string RPL_INVITELIST(const std::string &nick,
                                          const std::string &channel);
  // 337
  static const std::string RPL_ENDOFINVITELIST(const std::string &nick);
  // 341
  static const std::string RPL_INVITING(const std::string &nick,
                                        const std::string &input,
                                        const std::string &channel);
  // 443
  static const std::string ERR_USERONCHANNEL(const std::string &nick,
                                             const std::string &input,
                                             const std::string &channel);
  // BROADCAST
  static const std::string BC_INVITE(const std::string &sender,
                                     const std::string &nick,
                                     const std::string &channel);

  /* KICK  ----------------------------------------------------------------*/
  // BROADCAST
  static const std::string BC_KICK(const std::string &sender,
                                   const std::string &nick,
                                   const std::string &channel,
                                   const std::string &comment);

  /* KICK  ----------------------------------------------------------------*/
  // BROADCAST
  static const std::string BC_PART(const std::string &sender,
                                   const std::string &channel,
                                   const std::string &comment);

  /* TOPIC --------------------------------------------------------------*/
  // 331
  static const std::string RPL_NOTOPIC(const std::string &nick,
                                       const std::string &topic,
                                       const std::string &channel);
  // 332
  static const std::string RPL_TOPIC(const std::string &nick,
                                     const std::string &topic,
                                     const std::string &channel);
  // BROADCAST
  static const std::string BC_TOPIC(const std::string &sender,
                                    const std::string &channel,
                                    const std::string &comment);

  /* PRIVMSG --------------------------------------------------------------*/
  // 301
  static const std::string RPL_AWAY(const std::string &nick);
  // 404
  static const std::string ERR_CANNOTSENDTOCHAN(const std::string &server,
                                                const std::string &channel);
  // 407
  static const std::string ERR_TOOMANYTARGETS(const std::string &target,
                                              const std::string &targetsCount);
  // 411
  static const std::string ERR_NORECIPIENT(const std::string &nick,
                                           const std::string &command);
  // 412
  static const std::string ERR_NOTEXTTOSEND(const std::string &nick);
  // BROADCAST
  static const std::string BC_PRIVMSG(const std::string &sender,
                                      const std::string &target,
                                      const std::string &msg);

  /* JOIN --------------------------------------------------------------*/

  // 471
  static const std::string ERR_CHANNELISFULL(const std::string &nick,
                                             const std::string &channel);
  // 473
  static const std::string ERR_INVITEONLYCHAN(const std::string &nick,
                                              const std::string &channel);
  // 475
  static const std::string ERR_BADCHANNELKEY(const std::string &nick,
                                             const std::string &channel);
  // BROADCAST
  static const std::string BC_JOIN(const std::string &sender,
                                   const std::string &channel);

  /* NAMES --------------------------------------------------------------*/
  // 353
  static const std::string RPL_NAMREPLY(const std::string &nick,
                                        const std::string &list,
                                        const std::string &channel);
  // 366
  static const std::string RPL_ENDOFNAMES(const std::string &nick,
                                          const std::string &channel);

  /* LIST --------------------------------------------------------------*/
  // 321
  static const std::string RPL_LISTSTART(const std::string &nick);
  // 322
  static const std::string RPL_LIST(const std::string &nick,
                                    const std::string &channel,
                                    const std::string &count,
                                    const std::string &topic);
  // 323
  static const std::string RPL_LISTEND(const std::string &nick);
  ~Replies();
};
