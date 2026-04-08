#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <stdexcept>

class Client
{
private:
	int _fd;
	std::string _buffer;
	bool _authentificated;

public:
	// Client();
	// Client(const Client &copy);
	// Client &operator=(const Client &other);
	// Client(std::string name);

	// std::string name;

	int getFd() const;
	bool getAuth() const;
	std::string getBuffer() const;

	void setFd(int);
	void setBuffer(std::string buffer);
	void setAuth(bool);
	void appendBuffer(std::string const &temp);


	void send(const std::string &msg);
	~Client();
};

#endif
