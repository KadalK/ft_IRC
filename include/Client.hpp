#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <stdexcept>


class Client{
private:
	int _fd;
	bool _authentificated;
public:
	Client();
	Client(const Client& copy);
	Client& operator=(const Client& other);
	Client(std::string name);

	std::string name;

	int		getFd() const;
	bool	getAuth() const;
	void	setFd(int);
	void	setAuth(bool);

	void send(const std::string& msg);
	~Client();
};

#endif