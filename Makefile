# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lraffin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 04:32:29 by lraffin           #+#    #+#              #
#    Updated: 2021/10/19 15:40:15 by lraffin          ###   ########.fr        #
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
		\
		parsing/split/split.c \
		parsing/split/split_length.c \
		parsing/split/split_utils.c \
		\
		parsing/parser/parsing.c \
		parsing/parser/parsing_utils.c \
		parsing/parser/parse_commands.c \
		parsing/parser/parse_redirections.c \
		parsing/parser/pipe_fd.c \
		\
		parsing/interpreter/heredoc.c \
		parsing/interpreter/heredoc_env_var.c \
		parsing/interpreter/heredoc_special_value.c \
		parsing/interpreter/heredoc_split.c \
		\
		parsing/checker/check_input.c \
		parsing/checker/check_argv.c \
		parsing/checker/check_delimiters_1.c \
		parsing/checker/check_delimiters_2.c \
		parsing/checker/error_msg.c \
		\
		parsing/utils/get_paths.c \
		parsing/utils/libft.c \
		parsing/utils/linked_list.c \
		\
		shell/env/env.c \
		shell/env/list.c \
		shell/exec/exec.c \
		shell/exec/exec_command.c \
		shell/exec/exec_builtin.c \
		shell/exec/exec_pipes.c \
		shell/exec/exec_pipes_utils.c \
		shell/exec/fill_wildcard.c \
		shell/display.c \
		shell/error_msg.c \
		\
		exit/free.c \
		exit/error.c \
		\
		turtle/exit.c \
		turtle/init.c \
		turtle/list.c \
		turtle/main.c \
		turtle/raw.c \
		turtle/turtle.c \
		turtle/utils.c


### COMPILATION ###
CC		= clang
FLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
RDL		= -lreadline

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
	@$(CC) $(FLAGS) $(RDL) -L $(LIBFT_PATH) -o $@ $^ -lft
	@echo "$(GREEN)$@$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDE)/$(NAME).h
	@mkdir -p obj/turtle obj/builtin obj/parsing obj/parsing/parser obj/parsing/lexer
	@mkdir -p obj/parsing/split obj/parsing/checker obj/parsing/interpreter obj/parsing/utils
	@mkdir -p obj/shell/env obj/shell/exec obj/exit
	@$(CC) $(FLAGS) -I$(INCLUDE) -c -o $@ $<
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

norm:
	-@norminette $(SRC_PATH)
	-@norminette $(INCLUDE)

push:
	git add .
	git status
	git commit -m minishell
	git push

.PHONY:	all clean fclean re norm push
