#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

// class Commands;

class CommandsHandler {

private:
  PrivMsg *_pmsg;
  Password *_pass;
  Add all commands
  std::map<std::string, *Commands> commands;
  std::vector<std::string> tokens;

  CommandsHandler(const CommandsHandler &src);
  CommandsHandler &operator=(const CommandsHandler &rhs);

  Commands *findCommand(std::string inputCommand);
public:
  CommandsHandler();
  ~CommandsHandler();

  void processCommand(std::string rawMessage);

};

// class CommandsHandler {
//
// private:
//   std::map<std::string, std::string> commands; //debug test
//   std::vector<std::string> tokens;
//
//   CommandsHandler(const CommandsHandler &src);
//   CommandsHandler &operator=(const CommandsHandler &rhs);
//
//   std::string findCommand(std::string inputCommand);
// public:
//   CommandsHandler();
//   ~CommandsHandler();
//
//   void processCommand(std::string rawMessage);
//
// };
