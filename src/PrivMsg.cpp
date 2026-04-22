#include "Commands.hpp"
#include "PrivMsg.hpp"
#include "../include/PrivMsg.hpp"

// PrivMsg::PrivMsg() {}
// PrivMsg::PrivMsg(PrivMsg const &src) { (void)src; }
// PrivMsg::~PrivMsg() {};
// PrivMsg &PrivMsg::operator=(PrivMsg const &rhs) { (void)rhs; }
//
// void PrivMsg::execute(Client*, std::vector<std::string>)
// {
//
//   if (this->parsingMessage(p, rawText) != 0)
//     return (-1);//throw exception plus tard quoi en gros + errorMessage()
//
// }
//
// void parsingNickNames(std::string ){}
//
// size_t PrivMsg::parsingMessage(std::string rawText)
// {
//   size_t pos = rawText.find(':');
//   parsingNickNames(rawText.substr(0, pos));
//   p.textMessage = rawText + pos;


// PrivMsg::PrivMsg(){}



void PrivMsg::parsingMessage(std::string rawText){
	(void)rawText;
}

void PrivMsg::execute(Client* client, Server* server, std::vector<std::string> vector){
	(void)client;
	(void)server;
	(void)vector;
}

void PrivMsg::errorMessage(size_t errorValue){
	(void)errorValue;
}

PrivMsg::~PrivMsg(){}
