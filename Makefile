# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lraffin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 04:32:29 by lraffin           #+#    #+#              #
#    Updated: 2021/09/29 11:58:18 by lraffin          ###   ########.fr        #
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
		parsing/input.c \
		\
		shell/env/env.c \
		shell/exec/exec.c \
		shell/exec/exec_builtin.c \
		shell/display.c \
		\
		exit/free.c


### COMPILATION ###
CC		= clang
FLAGS	= -Wall -Wextra -Werror

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
	@$(CC) $(FLAGS) -L $(LIBFT_PATH) -o $@ $^ -lft
	@echo "$(GREEN)$@$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDE)/$(NAME).h
	@mkdir -p obj/builtin obj/parsing obj/shell/env obj/shell/exec obj/exit
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
