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
  bool _toDisconnect;

public:
  Client();

  int getFd() const;
  void setFd(int);

  bool getToDisconnect() const;
  void setToDisconnect(bool);

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

  std::string getAwayMsg() const;
  void setAwayMsg(std::string awayMsg);

  std::string getHostname() const;
  void setHostname(std::string hostname);

  std::string getNickname() const;
  void setNickname(std::string nickname);

  std::string getUsername() const;
  void setUsername(std::string username);

  std::string getTimeServ() const;
  void setTimeServ(std::string time);

  std::string getFullName() const;

  void setBuffer(std::string buffer);
  std::string getBuffer() const;

  void setBufferOut(std::string buffer);
  std::string getBufferOut() const;

  void appendBufferOut(std::string const &temp);

  std::string getFullInfo(std::string channel, bool isOpChan);

  void appendBuffer(std::string const &temp);
  bool isRegistered();
  ~Client();
};
