*This project has been created as part of the 42 curriculum by egache,kapinarc,tsaby.*

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
*Example:* `./ircserv 6667 1234`


Also we have implement a solution for running the executable in the background, you must provide a listening port and a connection password:

**Running the Mandatory Part:**

```bash
make run <port> <password>
```
*Example:* `make run 6667 1234`

```bash
make fclean
```

To connect to the server, configure your preferred IRC client to target `127.0.0.1` on the specified port, using the password you set.

**Running the Bonus Bot:**

The bot requires [Ollama](https://ollama.com/) to be installed. To run both the server and the bot simultaneously in the background:
```bash
make run-bot <port> <password>
```
*Example:* `make run-bot 6667 1234`

To shut down the background processes gracefully:
```bash
make fclean-bot
```

### About the Bot
The model used is Ollama3:8b

For run the Ollama's server:
```bash
ollama serve
```
To create the personality of the model, we need to use a Modelfile. This determines the behavior and customizes the model for a specific use.
In this project we implement a D&D Master.
```bash
ollama create <model_name> -f <Modelfile>
```
For run it:
```bash
ollama run <model_name>
```
At your first message, the D&D master attribute random stats and you can start your adventure !
When you run the bonus part you can chat with him, for that you have to do:
```bash
/QUERY <model_name>
```


## Features List

### Mandatory Commands
```bash
COMMAND <mandatory_args> [optionnal_args]
```

- **PASS <password\>**: Initial network password command. Must imperatively precede any other user registration commands.
- **NICK <nickname\>**: Sets or updates the nickname.
- **USER <user\> <host\> <srv\> <real\>**: Registers the client's system identity details to complete their formal registration.
- **JOIN <chan\> [<key\>]**: Joins a discussion channel. Creates the channel if it does not exist. Optional password argument if in `+k` mode.
- **PRIVMSG <target\> <text\>**: Transmits a text message to a specific target (either a user nickname or a public channel prefixed with `#`).
- **KICK <chan\> <user\> [<msg\>]**: Kicks a user from a channel.
- **INVITE <user\> <chan\>**: Officially invites a third-party user to join a channel. A crucial command to bypass restrictions on invite-only channels (`+i`).
- **TOPIC <chan\> [<topic\>]**:
  - **Without arguments:** Displays the channel's current topic.
  - **With arguments:** Changes or resets the topic
- **MODE <chan\> [<flags\>] [<args\>]**: Manages channel configuration and rights. Supported flags:
  - `i`: Set/remove Invite-only channel restriction.
  - `t`: Restrict TOPIC alterations to channel operators only.
  - `k`: Set/remove the channel key (password).
  - `o`: Give/take channel operator privilege.
  - `l`: Set/remove the user limit to the channel.

### Additional Commands
- **AWAY [<message\>]**: Marks the user as away and provides a public reason. Without arguments, it removes the away status.
- **WHO [<mask\>]**: Queries the server to selectively list user or channel information matching the given mask.
- **PART <chan\> [<msg\>]**: Formally leaves one or more channels, optionally broadcasting a parting message.
- **NAMES [<chan\>]**: Lists all currently connected users visible within the channel.
- **LIST [<chan\>]**: Lists all active channels on the server along with their topics and current member count.
- **QUIT [<message\>]**: Closes the current user session by disconnecting from the server with an optional reason.

## Resources

**References & Documentation:**
- [RFC 1459 - Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 - Internet Relay Chat: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [Ollama](https://ollama.com/)
- [Modern IRC Client Protocol](https://modern.ircdocs.horse)

**AI Usage:**
During the development of this project, Artificial Intelligence was utilized for the following specific tasks:
- **Bot Persona Configuration (Bonus):** AI (specifically the DeepSeek and Llama3 models) was used to structure the logic, rules, and system prompts inside the `Modelfile` scripts. This helped define the distinct personalities and rule-sets (like the text-based RPG Game Master) for the IRC bot.
- **Code Assistance & Refactoring:** AI tools were occasionally consulted to quickly identify syntax errors, understand C++98 specific limitations, and clarify edge cases regarding `epoll` and socket state management.
- **Completing and understanding unclear RFC's usage**: RFC 2812 is missing some documentation. AI helped us summarized best usage for some of the commands.
- **Readme redaction**: AI helped to structure the readme and formulate better sentences.
- **Modelfile:** AI tools were used to correct and translate modelfile's text to improve clarity and make it easier for the model to understand.
