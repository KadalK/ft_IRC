#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <stdexcept>
#include <string>

//single tone
class Client{
private:
	int _fd;
	bool _authenticated;
	std::string _name;

	Client(const Client& copy);
	Client& operator=(const Client& other);
public:
	Client();


	std::string	getName() const;
	int		getFd() const;
	bool	getAuth() const;
	void	setFd(int);
	void	setName(std::string name);
	void	setAuth(bool);

	void send(const std::string& msg);
	~Client();
};

#endif