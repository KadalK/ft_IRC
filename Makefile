# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2026/05/14 09:41:37 by tsaby            ###   ########.fr        #
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

all			:
				@$(MAKE) --no-print-directory $(NAME)


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

#*------------------------------------------------------------------------------*

clean		:
				@$(RM) -r $(OBJS_D)
				@echo "$(YELLOW)Clean complete$(NC)"

fclean		:	clean
				@$(RM) $(NAME)
				@echo "$(YELLOW)Full clean complete$(NC)"

re			:	fclean all

-include $(OBJS:.o=.d)

.PHONY: all  clean fclean re
