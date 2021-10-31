NAME			= minishell
CC				= gcc
RM				= rm -f
MKDIR			= mkdir -p
DEBUG			= 0
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
else
	MAKEFLAGS	= -j --output-sync=recurse --no-print-directory
	DEBUG_FLAGS	= -O2 -flto -D_FORTIFY_SOURCE=2 -fpie
endif
PROTECT_FLAGS	= -fno-exceptions -fstack-protector-all
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

SRCS			=	srcs/main.c\
					srcs/loop.c\
					srcs/lexer/lexer.c\
					srcs/lexer/var_lexeme.c\
					srcs/lexer/sub_lexemes.c\
					srcs/lexer/parse_lexemes.c\
					srcs/tokenizer/tokenizer.c\
					srcs/tokenizer/sub_tokens.c\
					srcs/tokenizer/prase_tokens.c\
					srcs/tokenizer/logic_tokenizer.c\
					srcs/exec/exec.c\
					srcs/exec/check_cmd.c\
					srcs/exec/exec_utils.c\
					srcs/utils/env.c\
					srcs/utils/ms_sub.c\
					srcs/utils/cd_sub.c\
					srcs/builtin/cd.c\
					srcs/builtin/exit.c\
					srcs/builtin/echo.c\
					srcs/builtin/env.c\
					srcs/builtin/pwd.c\
					srcs/builtin/unset.c\

OBJS			= $(notdir $(SRCS))
OBJS			:= $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.c=%.o))
NAME			:= $(addprefix $(BIN_DIR), $(NAME))
DEPS			= $(OBJS:.o=.d)
VPATH			= $(SRC_DIR):$(INC_DIR):$(BUILD_DIR)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT) $(GNL)
				$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/%.o:  $(SRC_DIR)/%.c
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

${GNL}:
				${MAKE} -C ${GNL_DIR}

${LIBFT}:
				${MAKE} -C ${LIBFT_DIR}

clean:
				$(RM) $(OBJS)
				$(RM) $(DEPS)
				cd import/get_next_line && $(MAKE) clean
				cd import/libft && $(MAKE) clean

fclean:
				$(RM) $(OBJS)
				$(RM) $(DEPS)
				cd import/get_next_line && $(MAKE) fclean
				cd import/libft && $(MAKE) fclean
				$(RM) $(NAME)

re:
				$(MAKE) fclean
				$(MAKE) all

ifeq ($(findstring $(MAKECMDGOALS), clean fclean re),)
	-include $(DEPS)
endif
.PHONY:			all, clean, fclean, re
