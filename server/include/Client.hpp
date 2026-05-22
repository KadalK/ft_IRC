#pragma once

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
  std::string _timeServ;
  std::string _awayMsg;

  bool _isAuth;
  bool _isAway;
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

  bool getAwayBool() const;
  void setAwayBool(bool);

  void setAwayMsg (std::string awayMsg);
  std::string getAwayMsg () const;

  void setHostname(std::string hostname);

  std::string getNickname() const;
  void setNickname(std::string nickname);

  std::string getUsername() const;
  void setUsername(std::string username);

  std::string getTimeServ() const;
  void setTimeServ(std::string time);

  std::string getHostname() const;

  std::string getFullName() const;

  std::string getBuffer() const;
  void setBuffer(std::string buffer);

  void setBufferOut(std::string buffer);
  std::string getBufferOut() const;

  void appendBufferOut(std::string const &temp);

  void appendBuffer(std::string const &temp);
  bool isRegistered();
  ~Client();
};
