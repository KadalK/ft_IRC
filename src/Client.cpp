#include "Client.hpp"

Client::Client() : _fd(-1), _nickname("NULL"),_username("NULL"),_bufferIn(),_bufferOut(),_isAuth(false),_hasPassword(false),_hasNickname(false),_hasUsername(false) {}

int		Client::getFd() const{
	return(this->_fd);
}
std::string		Client::getBuffer() const{
	return(this->_bufferIn);
}
std::string		Client::getBufferOut() const{
	return(this->_bufferOut);
}

bool	Client::getAuth() const
{
	return(this->_isAuth);
}

bool	Client::getUserBool() const
{
	return(this->_hasUsername);
}

bool	Client::getNickBool() const
{
	return(this->_hasNickname);
}

bool	Client::getPassBool() const
{
	return(this->_hasPassword);
}

std::string Client::getNickname() const
{
	return(this->_nickname);
}

std::string Client::getUsername() const
{
	return(this->_username);
}

void Client::setHostname(std::string hostname)
{
	this->_hostname = hostname;
}

void	Client::setAuth(bool state)
{
	this->_isAuth = state;
}
void	Client::setNickBool(bool state)
{
	this->_hasNickname = state;
}
void	Client::setPassBool(bool state)
{
	this->_hasPassword = state;
}
void	Client::setUserBool(bool state)
{
	this->_hasUsername = state;
}

void Client::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}
void Client::setUsername(std::string username)
{
	this->_username = username;
}

void	Client::setFd(int fd){
	this->_fd = fd;
}
void	Client::setBuffer(std::string buffer){
	this->_bufferIn = buffer;
}
void	Client::setBufferOut(std::string buffer){
	this->_bufferOut = buffer;
}

void Client::appendBufferOut(std::string const &temp)
{
	this->_bufferOut += temp;
}


void Client::appendBuffer(std::string const &temp) {
    this->_bufferIn += temp;
}

bool Client::isRegistered()
{
	if (this->_hasPassword == false)
	{
		this->appendBufferOut("Missing Password\n");
		return false;
	}
	if (this->_hasNickname == false)
	{
		this->appendBufferOut("Missing Nickname\n");
		return false;
	}
	if (this->_hasUsername == false)
	{
		this->appendBufferOut("Missing username\n");
		return false;
	}
	this->_isAuth = true;
	return true;
}

Client::~Client(){}
