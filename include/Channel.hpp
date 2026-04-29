#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include "Client.hpp"

class Channel {
private:
	std::string _name;
	std::string _topic;

  bool _inviteOnly;
  bool _topicRestrict;
  std::string _password;
  size_t _userLimit;
  size_t _userCount;

	std::map <Client*, bool> _clients;
  std::vector <Client*> _invited;
  
  void mode_i(bool flag, const std::string &arg);
  void mode_t(bool flag, const std::string &arg);
  void mode_k(bool flag, const std::string &arg);
  void mode_o(bool flag, const std::string &arg);
  void mode_l(bool flag, const std::string &arg);

public:
	Channel(const std::string& name);

	void	setTopic(std::string& topic);

	const std::string&	getName() const;
  const std::string&  getPassword() const;
	const std::string&	getTopic() const;
	bool	getInviteOnly() const;

  bool canJoinChannel(Client &client, std::string inPassword);

  bool isClientInvited(Client &client);
  bool isChannelFull(void);

	void	addClient(Client* client);
  void  inviteClient(Client* client);
	void	removeClient(Client* client);


	// void	broadcast(const std::string& msg, Client* sender);
	// bool	hasClient(Client* client) const;

	~Channel();
};

typedef void (Channel::*modeHandler)(bool flag, const std::string &arg);

#endif
