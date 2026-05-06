#pragma once

#include <iostream>

class Replies{
private:
	Replies();
public:

//privmsg
//411
	std::string ERR_NORECIPIENT(const std::string& server, const std::string& client, const std::string& command);
//412
std::string ERR_NOTEXTTOSEND(const std::string& server, const std::string& client);
//404
std::string ERR_CANNOTSENDTOCHAN(const std::string& server, const std::string& channel);
//414
// std::string ERR_WILDTOPLEVEL();
//407
std::string ERR_TOOMANYTARGETS(const std::string& server, const std::string& target, const std::string& abortMessage);
//301
std::string RPL_AWAY(const std::string& nick);

~Replies();
};