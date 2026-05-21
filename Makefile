# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2026/05/15 16:06:31 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW	:= \033[0;33m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SERVER_DIR := server
BOT_DIR    := bot
OLLAMA_PATH		:=	$(HOME)/sgoinfre/monique/bin
ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
ARG1 := $(word 1, $(ARGS))
ARG2 := $(word 2, $(ARGS))

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

run-bot		:	bot
					@echo "Starting Ollama engine in the background..."
					@export PATH=$(OLLAMA_PATH):$$PATH && ollama serve > /dev/null 2>&1 &
					@echo "Waiting 5 seconds for Ollama to initialize..."
					@sleep 5
					@echo "Checking/Creating the Monique model..."
					@export PATH=$(OLLAMA_PATH):$$PATH && ollama create monique -f $(BOT_DIR)/Modelfile > /dev/null 2>&1
					@echo "Starting the IRC bot in the background..."
					@./ircserv $(ARG1) $(ARG2) > serv.log 2>&1 &
					@./ircbot $(ARG1) $(ARG2) > bot.log 2>&1 &
					@echo "A bot.log exist in case of crash"
					@echo "Don't forget to type make fclean-bot to kill the proccessus after using the bot"

stop-bot	:
					@echo "Shutting down Ollama and the bot..."
					@-pkill -f "[o]llama serve"
					@-pkill -f "[i]rcbot"
					@-pkill -f "[i]rcserv"
					@echo "Everything has been properly shut down."

#*------------------------------------------------------------------------------*

clean:
	@$(MAKE) -C $(SERVER_DIR) clean
	@$(MAKE) -C $(BOT_DIR) clean

fclean: clean
	@$(MAKE) -C $(SERVER_DIR) fclean
	@$(MAKE) -C $(BOT_DIR) fclean
	@rm -f ircserv
	@rm -f ircbot
	@rm -f serv.log
	@rm -f bot.log

fclean-bot: fclean stop-bot

re: fclean all
re-bot: fclean-bot run-bot

.PHONY: all bot run run-bot stop-bot clean fclean fclean-bot re re-bot
%:
	@:
