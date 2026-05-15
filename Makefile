# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2026/05/15 12:30:59 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW	:= \033[0;33m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SRCS		:= \
				main.cpp \
				Server.cpp \
				Client.cpp \
				Channel.cpp \
				handlers/ClientHandler.cpp \
				handlers/ChannelHandler.cpp \
				handlers/CommandsHandler.cpp \
				commands/Join.cpp \
				commands/User.cpp \
				commands/Nick.cpp \
				commands/Pass.cpp \
				commands/PrivMsg.cpp \
				commands/Mode.cpp \
				commands/Topic.cpp \
				commands/Invite.cpp \
				commands/Kick.cpp \
				commands/Part.cpp \
				commands/Names.cpp \
				commands/List.cpp \
				Commands.cpp \
				Utils.cpp \
				Replies.cpp


#*------------------------------------------------------------------------------*

SRCS_D		:=	src/

OBJS_D		:=	objs/

#*------------------------------------------------------------------------------*

OBJS		:=	$(SRCS:%.cpp=$(OBJS_D)%.o)


#*------------------------------------------------------------------------------*

# HEAD		:= \
# 				include/Server.hpp \
# 				include/Client.hpp \
# 				include/Channel.hpp \
# 				include/ClientHandler.hpp \
# 				include/ChannelHandler.hpp \
# 				include/commands/Join.hpp \
# 				include/commands/User.hpp \
# 				include/commands/Nick.hpp \
# 				include/commands/Pass.hpp \
# 				include/commands/PrivMsg.hpp \
# 				include/commands/Topic.hpp \
# 				include/Commands.hpp
# 				include/Replies.hpp


HEAD_D		:=	.

CXX 		:= c++

#*------------------------------------------------------------------------------*

CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP -Iinclude

#*------------------------------------------------------------------------------*

NAME		:=	ircserv

#*------------------------------------------------------------------------------*

BOT_DIR			:=	src/bot
OLLAMA_PATH		:=	$(HOME)/sgoinfre/monique/bin

#*------------------------------------------------------------------------------*
ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

ARG1 := $(word 1, $(ARGS))
ARG2 := $(word 2, $(ARGS))

all			:
					@$(MAKE) --no-print-directory $(NAME)

bot			:	all
					@echo "Compiling the IRC bot..."
					@$(MAKE) -C $(BOT_DIR)
					@cp $(BOT_DIR)/bot ./ircbot
					@echo "Server and Bot successfully compiled!"

run-bot	:	bot
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
					@echo "Don't forget to type make stop-bot to kill the proccessus after using the bot"

stop-bot	:
					@echo "Shutting down Ollama and the bots..."
					@#(SIGTERM)
					
					@-pkill -15 "^ircbot$$" 2>/dev/null
					@-pkill -15 "^ircserv$$" 2>/dev/null
					@-pkill -15 -f "ollama serve" 2>/dev/null
					@echo "Everything has been properly shut down."
#*------------------------------------------------------------------------------*

$(NAME)		:	$(OBJS)
				@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo "$(YELLOW)$(NAME) successfully built!$(NC)"


$(OBJS_D)%.o:	$(SRCS_D)%.cpp
				@mkdir -p $(dir $@)
				@echo "$(YELLOW)Compiling $<...$(NC)"
				@$(CXX) $(CXXFLAGS) -c $< -o $@


# $(OBJS_D)	:
# 				@mkdir -p $(OBJS_D)
%:
	@:
#*------------------------------------------------------------------------------*

clean		:
					@$(RM) -r $(OBJS_D)
					@echo "$(YELLOW)Clean complete$(NC)"

fclean		:	clean
					@$(RM) $(NAME)
					@echo "$(YELLOW)Full clean complete$(NC)"

clean-bot	:
				@$(MAKE) -C $(BOT_DIR) clean

fclean-bot	: 	fclean stop-bot
					@$(MAKE) -C $(BOT_DIR) fclean
					@rm -f ./ircbot
					@rm -f bot.log
					@rm -f serv.log

re			:	fclean all

re-bot		:	fclean-bot run-bot

-include $(OBJS:.o=.d)

.PHONY: all  clean fclean re clean-bot fclean-bot re-bot stop-bot
