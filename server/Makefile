# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2026/05/21 17:52:08 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW	:= \033[0;33m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SRCS		:= \
				src/main.cpp \
				src/Server.cpp \
				src/Client.cpp \
				src/Channel.cpp \
				src/handlers/ClientHandler.cpp \
				src/handlers/ChannelHandler.cpp \
				src/handlers/CommandsHandler.cpp \
				src/commands/Join.cpp \
				src/commands/User.cpp \
				src/commands/Nick.cpp \
				src/commands/Pass.cpp \
				src/commands/PrivMsg.cpp \
				src/commands/Mode.cpp \
				src/commands/Topic.cpp \
				src/commands/Invite.cpp \
				src/commands/Kick.cpp \
				src/commands/Part.cpp \
				src/commands/Names.cpp \
				src/commands/List.cpp \
				src/commands/Away.cpp \
				src/commands/Who.cpp \
				src/Commands.cpp \
				../shared/Utils.cpp \
				src/Replies.cpp


#*------------------------------------------------------------------------------*

OBJS_D		:=	objs/
OBJS		:=	$(SRCS:%.cpp=$(OBJS_D)%.o)

#*------------------------------------------------------------------------------*

CXX 		:= c++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP -Iinclude -I../shared

#*------------------------------------------------------------------------------*

NAME		:=	ircserv

#*------------------------------------------------------------------------------*

all			: $(NAME)

#*------------------------------------------------------------------------------*

$(NAME)		:	$(OBJS)
				@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo "$(YELLOW)$(NAME) successfully built!$(NC)"


$(OBJS_D)%.o:	%.cpp
				@mkdir -p $(dir $@)
				@echo "$(YELLOW)Compiling $<...$(NC)"
				@$(CXX) $(CXXFLAGS) -c $< -o $@

#*------------------------------------------------------------------------------*

clean		:
					@$(RM) -r $(OBJS_D)
					@echo "$(YELLOW)Clean complete$(NC)"

fclean		:	clean
					@$(RM) $(NAME)
					@echo "$(YELLOW)Full clean complete$(NC)"

re : fclean all

-include $(OBJS:.o=.d)

.PHONY: all  clean fclean re
