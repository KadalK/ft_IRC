NAME    = bot

CXX     = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

SRCS_DIR = src/
OBJS_DIR = objs/

SRCS    = \
		  main.cpp \
          Bot.cpp \
          OllamaAPI.cpp

SRCS    := $(addprefix $(SRCS_DIR), $(SRCS))

OBJS    := $(SRCS:$(SRCS_DIR)%.cpp=$(OBJS_DIR)%.o)

DEPS    := $(OBJS:.o=.d)

# ---------------------------------------------------------------------------- #

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "bot built successfully"

# ---------------------------------------------------------------------------- #

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# ---------------------------------------------------------------------------- #

clean:
			rm -rf $(OBJS_DIR)

fclean: clean
			rm -f $(NAME)

re: fclean all

# ---------------------------------------------------------------------------- #

-include $(DEPS)

.PHONY: all clean fclean re
