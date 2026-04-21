# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2026/04/17 15:15:40 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW	:= \033[0;33m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SRCS		:=	main.cpp Channel.cpp  Client.cpp  Server.cpp  ManageChannel.cpp

#*------------------------------------------------------------------------------*

SRCS_D		:=	src/

OBJS_D		:=	objs/

#*------------------------------------------------------------------------------*

OBJS		:=	$(SRCS:%.cpp=$(OBJS_D)%.o)


#*------------------------------------------------------------------------------*

HEAD		:=	include/.hpp \ include/Channel.hpp  include/Client.hpp    include/Server.hpp include/ManageChannel.hpp


HEAD_D		:=	.

CXX 		:= c++

#*------------------------------------------------------------------------------*

CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP

#*------------------------------------------------------------------------------*

NAME		:=	IRC

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
