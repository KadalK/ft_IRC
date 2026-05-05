#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class Channel
{
private:
  std::string _name;
  std::string _topic;

  bool _inviteOnly;
  bool _topicRestrict;
  bool _hasPassword;
  bool _hasTopic;
  std::string _password;
  bool _hasUserLimit;
  size_t _userLimit;
  size_t _userCount;

  std::map<Client *, bool> _clients;
  std::vector<Client *> _invited;

  typedef void (Channel::*modeHandler)(bool flag, const std::string &arg,
                                       Client *sender);
  void mode_i(bool flag, const std::string &arg, Client *sender);
  void mode_t(bool flag, const std::string &arg, Client *sender);
  void mode_k(bool flag, const std::string &arg, Client *sender);
  void mode_o(bool flag, const std::string &arg, Client *sender);
  void mode_l(bool flag, const std::string &arg, Client *sender);

public:
  Channel(const std::string &name);

  std::map<char, modeHandler> _modeFt;

  void setTopic(std::string &topic);
  void setTopicBool(bool flag);

  const std::string &getName() const;
  const std::string &getPassword() const;
  const std::string &getTopic() const;
  bool getInviteOnly() const;
  bool getTopicRestrict() const;
  bool getHasTopic() const;

  bool canJoinChannel(Client &client, std::string inPassword);

  bool isClientInvited(Client &client);
  bool isClientInChannel(Client &client);
  bool isClientOperator(Client &client);
  bool isChannelFull(void);

  void addClient(Client *client);
  bool inviteClient(Client *client);
  void removeClient(Client *client);
  std::map<Client *, bool>::iterator findClientByNick(const std::string &nick);

  void replyJoinChannel(Client *client);
  std::string getClientInChan();

  size_t getUserCount() const;

  void broadcast(const std::string &msg, Client *sender);
  // bool	hasClient(Client* client) const;

  ~Channel();
};

#endif
