#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <stdexcept>
#include <string>

class Client
{
private:
	int _fd;

	//identity
	std::string _nickname;
	std::string _username;
	std::string _buffer;

	//state of connection
	bool _hasNick;
	bool _hasUser;
	bool _authenticated;

public:
	// Client();
	// Client(const Client &copy);
	// Client &operator=(const Client &other);

	const int& getFd() const;
	const bool& getAuth() const;
	std::string getBuffer() const; //jaurai kiffer mettre le GetBuffer en ref const pour ne pas faire de copie et que ca soit plus secure

	void setFd(int);
	void setBuffer(std::string buffer);
	void setAuth(bool);
	void appendBuffer(std::string const &temp);

	bool isRegistered() const;
	void send(const std::string &msg); // cette fonction set a envoyer un message au client exemple "Mot de passe trop court" ou "t moche"
	~Client();
};

#endif
