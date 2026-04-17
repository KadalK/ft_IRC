#include "Client.hpp"

// Client::Client() : name("No_name"), _fd(-1), _authentificated(false){}
// Client::Client(std::string name) : name(name), _fd(-1), _authentificated(false){
// 	if (name.length() > 9)
// 		std::length_error;
// }
// Client::Client(const Client& copy) : name(copy.name), _fd(copy._fd), _authentificated(copy._authentificated) {}
// Client& Client::operator=(const Client& other){
// 	if (this != &other)
// 	{
// 		this->name = other.name;
// 		this->_fd = other._fd;
// 		this->_authentificated = other._authentificated;
// 	}
// 	return (*this);
// }

int		Client::getFd() const{
	return(this->_fd);
}
std::string		Client::getBuffer() const{
	return(this->_buffer);
}

std::string		Client::getName() const{
	return(this->_name);
}

bool	Client::getAuth() const{
	return(this->_authenticated);
}

void	Client::setName(std::string name){
	this->_name = name;
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

// void Client::send(const std::string& msg){
// 	std::cout << "fonction send() of Client\n";
// }

Client::~Client(){}
