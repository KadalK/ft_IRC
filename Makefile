# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2026/05/20 18:15:00 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW	:= \033[0;33m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SERVER_DIR   := server
BOT_DIR      := bot
OLLAMA_PATH  := $(HOME)/sgoinfre/monique/bin
OLLAMA_MODELS_DIR := $(HOME)/sgoinfre/monique/models
ARGS         := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
ARG1         := $(word 1, $(ARGS))
ARG2         := $(word 2, $(ARGS))

#*------------------------------------------------------------------------------*

all			:
					@echo "Compiling the IRC serv..."
					@$(MAKE) -C $(SERVER_DIR)
					@cp $(SERVER_DIR)/ircserv ./ircserv


bot			:	all
					@echo "Compiling the IRC bot..."
					@$(MAKE) -C $(BOT_DIR)
					@cp $(BOT_DIR)/ircbot ./ircbot
					@echo "Server and Bot successfully compiled!"

run : all
					@echo "Server successfully compiled!"
					@echo "Starting the IRC serv in the background..."
					@./ircserv $(ARG1) $(ARG2) > serv.log 2>&1 &
					@echo "serv.log to check all logs"

run-v : all
					@echo "Server successfully compiled!"
					@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_serv.log ./ircserv $(ARG1) $(ARG2) > serv.log 2>&1 &
					@echo "Starting the IRC serv in the background..."
					@echo "serv.log to check all logs"
					@echo "valgrind_server.log to check valgrind logs"

stop	:
					@echo "Shutting down IRC server..."
					@-pkill -f "[i]rcserv"
					@-pkill -f "valgrind"
					@echo "Everything has been properly shut down."

run-bot		:	bot
					@echo "Starting Ollama engine in the background..."
					@export PATH=$(OLLAMA_PATH):$$PATH && export OLLAMA_MODELS=$(OLLAMA_MODELS_DIR) && ollama serve > /dev/null 2>&1 &
					@echo "Waiting 5 seconds for Ollama to initialize..."
					@sleep 5
					@echo "Checking/Creating the Monique model..."
					@export PATH=$(OLLAMA_PATH):$$PATH && export OLLAMA_MODELS=$(OLLAMA_MODELS_DIR) && ollama create monique -f $(BOT_DIR)/Modelfile > /dev/null 2>&1
					@echo "Starting the IRC bot and IRC serv in the background..."
					@./ircserv $(ARG1) $(ARG2) > serv.log 2>&1 &
					@./ircbot $(ARG1) $(ARG2) > bot.log 2>&1 &
					@echo "bot.log and serv.log to check all logs"
					@echo "Don't forget to type make fclean-bot to kill server and bot processus"

run-bot-v		:	bot
					@echo "Starting Ollama engine in the background..."
					@export PATH=$(OLLAMA_PATH):$$PATH && export OLLAMA_MODELS=$(OLLAMA_MODELS_DIR) && ollama serve > /dev/null 2>&1 &
					@echo "Waiting 10 seconds for Ollama to initialize..."
					@sleep 10
					@echo "Checking/Creating the Monique model..."
					@export PATH=$(OLLAMA_PATH):$$PATH && export OLLAMA_MODELS=$(OLLAMA_MODELS_DIR) && ollama create monique -f $(BOT_DIR)/Modelfile
					@echo "Starting the IRC bot and IRC serv in the background..."
					@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_serv.log ./ircserv $(ARG1) $(ARG2) > serv.log 2>&1 &
					@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_bot.log ./ircbot $(ARG1) $(ARG2) > bot.log 2>&1 &
					@echo "bot.log and serv.log to check all logs"
					@echo "valgrind_bot.log and valgrind_server.log to check valgrind logs"
					@echo "Don't forget to type make fclean-bot to kill server and bot processus"

stop-bot	:
					@echo "Shutting down Ollama and the bot..."
					@-pkill -f "[o]llama serve"
					@-pkill -f "[i]rcbot"

#*------------------------------------------------------------------------------*
clean:
	@$(MAKE) -C $(SERVER_DIR) clean
	@$(MAKE) -C $(BOT_DIR) clean

fclean: clean stop
	@$(MAKE) -C $(SERVER_DIR) fclean
	@$(MAKE) -C $(BOT_DIR) fclean
	@rm -f ircserv ircbot
	@rm -f serv.log bot.log
	@rm -f valgrind_serv.log valgrind_bot.log

fclean-bot: fclean stop-bot
	@$(MAKE) -C $(BOT_DIR) fclean
	@rm -f ircbot
	@rm -f bot.log
	@rm -f valgrind_bot.log

re: fclean all
re-bot: fclean-bot run-bot

.PHONY: all bot run run-v stop run-bot run-bot-v stop-bot clean fclean fclean-bot re re-bot
%:
	@:
