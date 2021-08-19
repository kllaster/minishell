NAME			= minishell
CC				= gcc
RM				= rm -f
MKDIR			= mkdir -p
DEBUG			= 0
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
endif
COMMON_FLAGS	= -Wall -Wextra -Werror -MMD
CFLAGS			= $(COMMON_FLAGS) $(DEBUG_FLAGS) -march=native -O2 -msse4a -flto -pipe

BIN_DIR			= ./
BUILD_DIR		= build/
HEADERS			= include/

SRCS				= srcs/main.c\

OBJS			= $(notdir $(SRCS))
OBJS			:= $(OBJS:%.c=$(BUILD_DIR)%.o)
DEPS			= $(OBJS:.o=.d)
NAME 			:= $(addprefix $(BIN_DIR), $(NAME))

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -I $(HEADERS) $(OBJS) -o $(NAME)

$(OBJS):		$(SRCS)
				$(MKDIR) $(dir $@)
				$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
				$(RM) $(OBJS)
				$(RM) $(DEPS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

-include		$(DEPS)
.PHONY:			all, clean, fclean, re