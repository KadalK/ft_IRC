*This project has been created as part of the 42 curriculum by tsaby,egache,kapinarc.*

## Description
The **ft_irc** project aims to create a fully functional Internet Relay Chat (IRC) server from scratch using C++98. The goal is to deeply understand network programming, TCP/IP protocols, and non-blocking I/O multiplexing.

Our server acts as a central hub where users can connect via standard IRC clients (such as Irssi, WeeChat, Hexchat or simply `nc`). It supports authentication, real-time private messaging, channel creation, and a robust set of channel operator commands (KICK, INVITE, TOPIC, and MODE limits/passwords/privileges). All client interactions are handled concurrently without threading or forking, using a single `epoll` instance. Additionally, a bonus AI-driven IRC bot has been implemented to interact with users directly in the chat.

## Instructions

### Compilation
A `Makefile` is provided to compile the source code cleanly.
- Compile the IRC server:
  ```bash
  make
  ```
- Compile the bonus AI bot:
  ```bash
  make bot
  ```
- Clean up object files and executables:
  ```bash
  make clean
  make fclean
  ```

### Execution
To start the IRC server, you must provide a listening port and a connection password:

```bash
./ircserv <port> <password>
```
*Example:* `./ircserv 6667 my_password`

Also we have implement a solution for running the executable in the backround, you must provide a listening port and a connection password:

```bash
make run ARG1=<port> ARG2=<password>
```

To connect to the server, configure your preferred IRC client to target `127.0.0.1` on the specified port, using the password you set.

**Running the Bonus Bot:**
The bot requires [Ollama](https://ollama.com/) to be installed. To run both the server and the bot simultaneously in the background:
```bash
make run-bot ARG1=<port> ARG2=<password>
```
To shut down the background processes gracefully:
```bash
make fclean-bot
```

## Resources

**References & Documentation:**
- [RFC 1459 - Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 - Internet Relay Chat: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [Ollama GitHub Repository](https://github.com/ollama/ollama)

**AI Usage:**
During the development of this project, Artificial Intelligence was utilized for the following specific tasks:
- **Bot Persona Configuration (Bonus):** AI (specifically the DeepSeek and Llama3 models) was used to structure the logic, rules, and system prompts inside the `Modelfile` scripts. This helped define the distinct personalities and rule-sets (like the text-based RPG Game Master) for the IRC bot.
- **Code Assistance & Refactoring:** AI tools were occasionally consulted to quickly identify syntax errors, understand C++98 specific limitations, and clarify edge cases regarding `epoll` and socket state management.
