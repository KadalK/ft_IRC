#include "Client.hpp"
#include "Replies.hpp"

Client::Client()
    : _fd(-1), _nickname("*"), _username("*"), _bufferIn(), _bufferOut(),
      _isAuth(false),_isAway(false), _hasPassword(false), _hasNickname(false),
      _hasUsername(false), _toDisconnect(false)
{
}

bool Client::getToDisconnect() const{
  return(this->_toDisconnect);
}

void Client::setToDisconnect(bool state){
  this->_toDisconnect = state;
}

int Client::getFd() const { return (this->_fd); }

std::string Client::getBuffer() const { return (this->_bufferIn); }

std::string Client::getBufferOut() const { return (this->_bufferOut); }

bool Client::getAuth() const { return (this->_isAuth); }

bool Client::getAwayBool() const { return (this->_isAway); }

bool Client::getUserBool() const { return (this->_hasUsername); }

bool Client::getNickBool() const { return (this->_hasNickname); }

bool Client::getPassBool() const { return (this->_hasPassword); }

std::string Client::getNickname() const { return (this->_nickname); }

std::string Client::getUsername() const { return (this->_username); }

std::string Client::getHostname() const { return (this->_hostname); }

std::string Client::getTimeServ() const { return (this->_timeServ); }

std::string Client::getAwayMsg() const { return (this->_awayMsg); }

void Client::setTimeServ(std::string time) { this->_timeServ = time; }

void Client::setAwayMsg(std::string awayMsg) { this->_awayMsg = awayMsg; }

std::string Client::getFullName() const
{
  return (":" + this->getNickname() + "!" + this->getUsername() + "@" +
          this->getHostname());
}

std::string Client::getFullInfo(std::string channel, bool isOpChan)
{
  std::string flags = (this->getAwayBool() == true) ? "G" : "H";
  flags += (isOpChan == true) ? "@" : "";
  return (channel + " " + this->getUsername() + " " + this->getHostname() +
          " ircserv " + this->getNickname() + " " + flags + " :0 *");
}

void Client::setHostname(std::string hostname) { this->_hostname = hostname; }

void Client::setAuth(bool state)
{
  this->_isAuth = state;
  std::string client, nick, time;
  client = this->getFullName();
  nick = this->getNickname();
  time = this->_timeServ;
  this->appendBufferOut(
      Replies::RPL_WELCOME(client, nick) + Replies::RPL_YOURHOST(nick) +
      Replies::RPL_CREATED(nick, time) + Replies::RPL_MYINFO(nick));
}
void Client::setNickBool(bool state) { this->_hasNickname = state; }
void Client::setPassBool(bool state) { this->_hasPassword = state; }
void Client::setUserBool(bool state) { this->_hasUsername = state; }
void Client::setAwayBool(bool state) { this->_isAway = state; }

void Client::setNickname(std::string nickname) { this->_nickname = nickname; }
void Client::setUsername(std::string username) { this->_username = username; }

void Client::setFd(int fd) { this->_fd = fd; }
void Client::setBuffer(std::string buffer) { this->_bufferIn = buffer; }
void Client::setBufferOut(std::string buffer) { this->_bufferOut = buffer; }

void Client::appendBufferOut(std::string const &temp)
{
  this->_bufferOut += temp;
}

void Client::appendBuffer(std::string const &temp) { this->_bufferIn += temp; }

bool Client::isRegistered()
{
  if (this->_hasPassword == false || this->_hasNickname == false ||
      this->_hasUsername == false)
    return false;
  this->_isAuth = true;
  return true;
}

Client::~Client() {}
