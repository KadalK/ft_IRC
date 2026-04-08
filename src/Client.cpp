#include "Client.hpp"

Client::Client() : _name("No__name"), _fd(-1), _authenticated(false){}

Client::Client(const Client& copy) : _name(copy._name), _fd(copy._fd), _authenticated(copy._authenticated) {}
Client& Client::operator=(const Client& other){
	if (this != &other)
	{
		this->_name = other._name;
		this->_fd = other._fd;
		this->_authenticated = other._authenticated;
	}
	return (*this);
}

int		Client::getFd() const{
	return(this->_fd);
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

void	Client::setAuth(bool auth){
	this->_authenticated = auth;
}

void Client::send(const std::string& msg){
	(void)msg;
	std::cout << "fonction send() of Client\n";
}

Client::~Client(){}