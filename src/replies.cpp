#include "../include/replies.hpp"

//411
std::string Replies::ERR_NORECIPIENT(const std::string& server, const std::string& client, const std::string& command)
{
	return (":" + server + " 411 " + client + " :No recipient given (" + command + ")\r\n");
}

//412
std::string Replies::ERR_NOTEXTTOSEND(const std::string& server,  const std::string& client){
	return (":" + server + " 412 " + client + " :No text to send\r\n");
}

//404
std::string Replies::ERR_CANNOTSENDTOCHAN(const std::string& server, const std::string& channel){
	return (":" + server + " 404 " + channel + " :Cannot send to channel\r\n");
}

//414
// std::string Replies::ERR_WILDTOPLEVEL(){}

//407
std::string Replies::ERR_TOOMANYTARGETS(const std::string& server, const std::string& target, const std::string& abortMessage){
	return (":" + server + " 407 " + target + " :407 recipients. " + abortMessage + "\r\n");
}

//301
std::string RPL_AWAY(const std::string& server, const std::string& nick,const std::string& awayMsg){
	return (":" + server + " 301 " + nick + " :" + awayMsg + "\r\n");
}