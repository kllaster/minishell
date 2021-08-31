NAME			= minishell
CC				= gcc
RM				= rm -f
MKDIR			= mkdir -p
DEBUG			= 0
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
else
	DEBUG_FLAGS = -march=native -O2 -flto -msse4a -D_FORTIFY_SOURCE=2 -fpie
endif
PROTECT_FLAGS	= -fno-exceptions -fcf-protection=full -fstack-protector-all
COMMON_FLAGS	= -std=c99 -Wall -Wextra -Werror -Wfloat-equal -MMD -pipe
CFLAGS			= $(COMMON_FLAGS) $(DEBUG_FLAGS) $(PROTECT_FLAGS)

BIN_DIR			= ./
SRC_DIR			= srcs
BUILD_DIR		= build
INC_DIR			= include

GNL_DIR			= import/get_next_line
GNL				= ${GNL_DIR}/bin/get_next_line.a
LIBFT_DIR		= import/libft
LIBFT			= ${LIBFT_DIR}/bin/libft.a

LIBS			= ${LIBFT} ${GNL} -ltermcap

SRCS			= $(shell find $(SRC_DIR) -name "*.c")

OBJS			= $(notdir $(SRCS))
OBJS			:= $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.c=%.o))
NAME			:= $(addprefix $(BIN_DIR), $(NAME))
DEPS			= $(OBJS:.o=.d)
VPATH			= $(SRC_DIR):$(INC_DIR):$(BUILD_DIR)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT) $(GNL)
				$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/%.o: %.c
				$(MKDIR) $(dir $@)
				$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

${GNL}:
				${MAKE} -C ${GNL_DIR}

${LIBFT}:
				${MAKE} -C ${LIBFT_DIR}

clean:
				cd import/get_next_line && $(MAKE) clean
				cd import/libft && $(MAKE) clean

fclean:
				$(RM) $(OBJS)
				$(RM) $(DEPS)
				cd import/get_next_line && $(MAKE) fclean
				cd import/libft && $(MAKE) fclean
				$(RM) $(NAME)

re:				fclean all

-include		$(DEPS)
.PHONY:			all, clean, fclean, re