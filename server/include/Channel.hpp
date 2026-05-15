#pragma once

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class Client;

class Channel
{
private:
  std::string _name;
  std::string _topic;
  std::string _password;
  std::string _creationTime;

  bool _inviteOnly;
  bool _topicRestrict;
  bool _hasPassword;
  bool _hasTopic;
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
  bool getHasPassword() const;
  bool getHasTopic() const;
  bool getHasUserLimit() const;
  size_t getUserCount() const;
  size_t getUserLimit() const;
  std::string getUserLimitString() const;
  std::string getUserCountString() const;
  const std::string getModeString() const;
  const std::map<Client *, bool> &getClients() const;
  const std::string &getTime();

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

  void broadcast(const std::string &msg, Client *sender, bool excluded);

  ~Channel();
};
