# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lraffin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 04:32:29 by lraffin           #+#    #+#              #
#    Updated: 2021/11/11 16:58:59 by lraffin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME	= minishell

### SOURCE FILES ###
SOURCES = \
		main.c \
		init.c \
		clean.c \
		\
		builtin/echo.c \
		builtin/cd.c \
		builtin/pwd.c \
		builtin/env.c \
		builtin/history.c \
		builtin/export.c \
		builtin/unset.c \
		builtin/exit.c \
		\
		parsing/lexer/upgrade_input.c \
		parsing/lexer/env_var.c \
		parsing/lexer/env_var_length.c \
		parsing/lexer/env_var_utils.c \
		parsing/lexer/pid_value.c \
		parsing/lexer/ret_value.c \
		parsing/lexer/utils.c \
		parsing/lexer/equal_sign.c \
		\
		parsing/split/split.c \
		parsing/split/split_length.c \
		parsing/split/split_utils.c \
		\
		parsing/parser/parsing.c \
		parsing/parser/bin_cmd.c \
		parsing/parser/builtin_cmd.c \
		parsing/parser/heredoc.c \
		parsing/parser/utils.c \
		parsing/parser/fill_cmd.c \
		parsing/parser/redirections.c \
		parsing/parser/pipes.c \
		parsing/parser/parentheses.c \
		\
		parsing/heredoc/heredoc.c \
		parsing/heredoc/input.c \
		parsing/heredoc/env_var.c \
		parsing/heredoc/special_value.c \
		parsing/heredoc/split.c \
		\
		parsing/checker/input.c \
		parsing/checker/argv.c \
		parsing/checker/delimiters_1.c \
		parsing/checker/delimiters_2.c \
		parsing/checker/error_msg.c \
		parsing/checker/unclosed_char.c \
		\
		parsing/utils/get_paths.c \
		parsing/utils/libft_1.c \
		parsing/utils/libft_2.c \
		parsing/utils/linked_list.c \
		parsing/utils/print_list.c \
		\
		env/env.c \
		env/list.c \
		\
		exec/exec.c \
		exec/bin_cmd.c \
		exec/cmd_array.c \
		exec/builtin_cmd.c \
		exec/pipes.c \
		exec/pipes_utils.c \
		exec/close_fd.c \
		exec/parentheses.c \
		exec/wildcard.c \
		\
		shell/display.c \
		shell/error_msg.c \
		\
		exit/free.c \
		exit/error.c \
		\
		turtle/exit.c \
		turtle/init.c \
		turtle/list.c \
		turtle/unused.c \
		turtle/raw.c \
		turtle/turtle.c \
		turtle/utils.c


### COMPILATION ###
CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g3 -I$(INCLUDE) #$(DEBUG_F)
DEBUG_F	= -fsanitize=address
LIBS	= -lft -lncurses -lreadline

### INCLUDES ###
INCLUDE		= inc
LIBFT_PATH	= libft
SRC_PATH	= src
OBJ_PATH	= obj

### OBJECTS ###
SRC	= $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJ	= $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

### COLORS ###
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### RULES ###

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)libft..$(NOC)"
	@make -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) -L $(LIBFT_PATH) -o $@ $^ $(LIBS)
	@echo "$(GREEN)$@$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDE)/$(NAME).h
	@mkdir -p obj/turtle obj/builtin obj/parsing obj/parsing/parser obj/parsing/lexer
	@mkdir -p obj/parsing/split obj/parsing/checker obj/parsing/heredoc obj/parsing/utils
	@mkdir -p obj/env obj/exec obj/exit obj/shell
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(BLUE)clang $(WHITE)$(notdir $@)$(NOC)"

clean:
	@echo "$(RED)clean$(NOC)"
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

debug: CFLAGS += $(DEBUG_F)
debug: fclean
debug: re

norm:
	-@norminette $(SRC_PATH)
	-@norminette $(INCLUDE)

push:
	git add .
	git status
	git commit -m minishell
	git push

.PHONY:	all clean fclean re debug norm push
