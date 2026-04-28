# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2026/04/22 11:22:53 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW	:= \033[0;33m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SRCS		:=	main.cpp \
				Channel.cpp \
				Client.cpp \
				Server.cpp \
				ManageChannel.cpp \
				Commands.cpp \
				Pass.cpp \
				PrivMsg.cpp \
				Nick.cpp

#*------------------------------------------------------------------------------*

SRCS_D		:=	src/

OBJS_D		:=	objs/

#*------------------------------------------------------------------------------*

OBJS		:=	$(SRCS:%.cpp=$(OBJS_D)%.o)


#*------------------------------------------------------------------------------*

HEAD		:=	include/Channel.hpp \
				include/Client.hpp \
				include/Channel.hpp \
				include/ClientHandler.hpp \
				include/ChannelHandler.hpp \
				include/CommandsHandler \
				include/Commands.hpp
				include/Join.hpp \
				include/Nick.hpp

HEAD_D		:=	.

CXX 		:= c++

#*------------------------------------------------------------------------------*

CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP

#*------------------------------------------------------------------------------*

NAME		:=	ircserv

#*------------------------------------------------------------------------------*

all			:
				@$(MAKE) --no-print-directory $(NAME)


#*------------------------------------------------------------------------------*

$(NAME)		:	$(OBJS_D) $(OBJS)
				@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo "$(YELLOW)$(NAME) successfully built!$(NC)"


$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.cpp | $(OBJS_D)
				@echo "$(YELLOW)Compiling $<,...$(NC)"
				@$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@


$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

#*------------------------------------------------------------------------------*

clean		:
				@$(RM) -r $(OBJS) $(OBJS_D)
				@echo "$(YELLOW)Clean complete$(NC)"

fclean		:	clean
				@$(RM) $(NAME)
				@echo "$(YELLOW)Full clean complete$(NC)"

re			:	fclean all

-include $(OBJS:.o=.d)

.PHONY: all  clean fclean re
