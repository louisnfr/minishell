# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 04:32:29 by lraffin           #+#    #+#              #
#    Updated: 2021/10/07 12:56:26 by EugenieFran      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME	= minishell

### SOURCE FILES ###
SOURCES = \
		main.c \
		\
		builtin/echo.c \
		builtin/cd.c \
		builtin/pwd.c \
		builtin/env.c \
		builtin/export.c \
		builtin/unset.c \
		builtin/exit.c \
		\
		parsing/parsing.c \
		parsing/check_input.c \
		parsing/upgrade_input.c \
		parsing/env_variable/handle_env_var.c \
		parsing/env_variable/get_new_length.c \
		parsing/env_variable/utils.c \
		parsing/split/split_arguments.c \
		parsing/split/handle_delimiters.c \
		parsing/split/utils.c \
		parsing/parsing_utils.c \
		parsing/parse_commands.c \
		parsing/get_paths.c \
		parsing/libft.c \
		parsing/linked_list.c \
		\
		shell/env/env.c \
		shell/env/list.c \
		shell/exec/exec.c \
		shell/exec/exec_builtin.c \
		shell/display.c \
		\
		exit/free.c \
		exit/error.c


### COMPILATION ###
CC		= clang
FLAGS	= -Wall -Wextra -Werror
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
	@mkdir -p obj/builtin obj/parsing obj/parsing/env_variable obj/parsing/split obj/shell/env obj/shell/exec obj/exit
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
