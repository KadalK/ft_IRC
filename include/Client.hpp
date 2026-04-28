#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <stdexcept>
#include <string>

class Client
{
private:
	int _fd;
	std::string _nickname;
	std::string _username;
  std::string _hostname;
	std::string _bufferIn;
	std::string _bufferOut;

	bool _isAuth;
	bool _hasPassword;
	bool _hasNickname;
	bool _hasUsername;

public:
	Client();

	int getFd() const;
	void setFd(int);

	bool getUserBool() const;
	void setUserBool(bool);

	bool getPassBool() const;
	void setPassBool(bool);

	bool getNickBool() const;
	void setNickBool(bool);

	bool getAuth() const;
	void setAuth(bool);

	std::string getNickname() const;
	void setNickname(std::string nickname);

	std::string getUsername() const;
	void setUsername(std::string username);

	std::string getBuffer() const;
	void setBuffer(std::string buffer);

	void setBufferOut(std::string buffer);
	std::string getBufferOut() const;

	void appendBuffer(std::string const &temp);
	bool isRegistered();
	~Client();
};

#endif
