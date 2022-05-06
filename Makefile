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

BIN_DIR			=
SRC_DIR			= srcs
TESTS_DIR		= tests
BUILD_DIR		= build
INC_DIR			= include

GNL_DIR			= import/get_next_line
GNL				= ${GNL_DIR}/bin/get_next_line.a
LIBFT_DIR		= import/libft
LIBFT			= ${LIBFT_DIR}/bin/libft.a

LIBS			= ${LIBFT} ${GNL}

MAIN_SRC        =	srcs/main.c
SRCS			=	srcs/loop.c\
					srcs/lexer/lexer.c\
					srcs/lexer/var_lexeme.c\
					srcs/lexer/sub_lexemes.c\
					srcs/lexer/parse_lexemes.c\
					srcs/tokenizer/tokenizer.c\
					srcs/tokenizer/sub_tokens.c\
					srcs/tokenizer/prase_tokens.c\
					srcs/tokenizer/tokenize_logic.c\
					srcs/exec/exec.c\
					srcs/exec/check_cmd.c\
					srcs/exec/exec_utils.c\
					srcs/utils/env.c\
					srcs/utils/ms_sub.c\
					srcs/utils/signal.c\
					srcs/builtin/cd.c\
					srcs/builtin/exit.c\
					srcs/builtin/echo.c\
					srcs/builtin/env.c\
					srcs/builtin/pwd.c\
					srcs/builtin/unset.c\

MAIN_OBJ		= $(subst $(SRC_DIR), $(BUILD_DIR), $(MAIN_SRC:%.c=%.o))
OBJS			= $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.c=%.o))
NAME			:= $(addprefix $(BIN_DIR), $(NAME))
DEPS			= $(OBJS:.o=.d)
VPATH			= $(SRC_DIR):$(INC_DIR):$(BUILD_DIR)

TESTS = $(shell find $(TESTS_DIR) -name '*.check')
TESTS_SRC_DIR = $(TESTS_DIR)/$(SRC_DIR)
TESTS_BUILD_DIR = $(TESTS_DIR)/$(BUILD_DIR)
TESTS_BIN_DIR = $(TESTS_DIR)/bin
TESTS_BIN_PATH = $(TESTS_BIN_DIR)/test_

TESTS_SRCS := $(subst $(TESTS_DIR), $(TESTS_SRC_DIR), $(TESTS:%.check=%.c))
TESTS_OBJS := $(subst $(TESTS_SRC_DIR), $(TESTS_BUILD_DIR), $(TESTS_SRCS:%.c=%.o))
TESTS_BINS := $(subst $(TESTS_BUILD_DIR)/, $(TESTS_BIN_PATH), $(TESTS_OBJS:%.o=%))

all:			$(NAME)

$(NAME):		$(MAIN_OBJ) $(OBJS) $(LIBFT) $(GNL)
				$(CC) $(CFLAGS) -I $(INC_DIR) $(MAIN_OBJ) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/%.o:  $(SRC_DIR)/%.c
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

${GNL}:
				${MAKE} -C ${GNL_DIR}

${LIBFT}:
				${MAKE} -C ${LIBFT_DIR}

test:			$(TESTS_BINS) $(TESTS_SRCS) $(TESTS_OBJS)
				./$<

test_leaks:		$(TESTS_BINS) $(TESTS_SRCS) $(TESTS_OBJS)
				./$<
				CK_FORK=no leaks --atExit -- ./$<

$(TESTS_SRC_DIR)/%.c: $(TESTS_DIR)/%.check
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				checkmk $< > $@

$(TESTS_BUILD_DIR)/%.o: $(TESTS_SRC_DIR)/%.c
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(TESTS_BIN_PATH)%:	$(TESTS_BUILD_DIR)/%.o $(OBJS)
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) $< $(LIBS) -lcheck -o $@

test_clean:
				$(RM) $(TESTS_SRCS)
				$(RM) -rd $(TESTS_SRC_DIR)
				$(RM) $(TESTS_OBJS)
				$(RM) -rd $(TESTS_BUILD_DIR)

test_fclean:	test_clean
				$(RM) $(TESTS_BINS)
				$(RM) -rd $(TESTS_BIN_DIR)

clean:			test_clean
				$(RM) $(OBJS)
				$(RM) $(DEPS)
				cd import/get_next_line && $(MAKE) clean
				cd import/libft && $(MAKE) clean

fclean:			clean test_fclean
				$(RM) -rd $(BUILD_DIR)
				$(RM) $(NAME)

re:
				$(MAKE) fclean
				$(MAKE) all

-include $(DEPS)
.PHONY:			all, clean, fclean, re
