NAME		= minishell
CC			= gcc
RM			= rm -f
DEBUG		= 0
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
endif
CFLAGS		= -Wall -Wextra -Werror -MMD $(DEBUG_FLAGS)
CPPFLAGS	= $(CFLAGS) -march=native -O2 -msse4a -flto -pipe
HEADERS		= include/

SRCS =	src/main.c\

OBJS = $(SRCS:.c=.o)

$(NAME):		$(OBJS)
				$(CC) $(CPPFLAGS) -I $(HEADERS) $(OBJS) -o $(NAME)

all:			$(NAME)

.c.o:
				$(CC) $(CPPFLAGS) -I $(HEADERS) -o $@ -c $<

$(OBJS):		$(HEADERS)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS:.o=.d)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

re_rt:			clean all

.PHONY:			all clean fclean re re_rt
.SILENT: