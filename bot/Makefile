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

SRCS		:= \
		  	src/main.cpp \
      	src/Bot.cpp \
      	src/OllamaAPI.cpp \
				../shared/Utils.cpp


#*------------------------------------------------------------------------------*

OBJS_D		:=	objs/
OBJS		:=	$(SRCS:%.cpp=$(OBJS_D)%.o)

#*------------------------------------------------------------------------------*

CXX 		:= c++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -g3 -MMD -MP -Iinclude -I../shared

#*------------------------------------------------------------------------------*

NAME		:=	ircbot

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
