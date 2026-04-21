#include "Client.hpp"

// Client::Client() : name("No_name"), _fd(-1), _authenticated(false){}
// Client::Client(std::string name) : name(name), _fd(-1), _authenticated(false){
// 	if (name.length() > 9)
// 		std::length_error;
// }
// Client::Client(const Client& copy) : name(copy.name), _fd(copy._fd), _authenticated(copy._authenticated) {}
// Client::Client() : name("No_name"), _fd(-1), _authenticated(false){}
// Client::Client(std::string name) : name(name), _fd(-1), _authenticated(false){
// 	if (name.length() > 9)
// 		std::length_error;
// }
// Client::Client(const Client& copy) : name(copy.name), _fd(copy._fd), _authenticated(copy._authenticated) {}
// Client& Client::operator=(const Client& other){
// 	if (this != &other)
// 	{
// 		this->name = other.name;
// 		this->_fd = other._fd;
// 		this->_authenticated = other._authenticated;
// 		this->_authenticated = other._authenticated;
// 	}
// 	return (*this);
// }


const int&		Client::getFd() const{
	return(this->_fd);
}
std::string Client::getBuffer() const{
	return this->_buffer;
}

const bool&	Client::getAuth() const{
	return(this->_authenticated);
}

void	Client::setFd(int fd){
	this->_fd = fd;
}
void	Client::setBuffer(std::string buffer){
	this->_buffer = buffer;
}

void	Client::setAuth(bool auth){
	this->_authenticated = auth;
}

void Client::appendBuffer(std::string const &temp) {
	this->_buffer += temp;
}

bool Client::isRegistered() const{
	if (this->_authenticated && this->_hasNick && this->_hasUser)
		return (true);
	return (false);
}

void Client::send(const std::string& msg){
	(void)msg;
	std::cout << "fonction send() of Client\n";
}

// void Client::send(const std::string& msg){
// 	std::cout << "fonction send() of Client\n";
// }

Client::~Client(){}
