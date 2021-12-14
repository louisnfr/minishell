# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 04:32:29 by lraffin           #+#    #+#              #
#    Updated: 2021/12/14 15:01:28 by lraffin          ###   ########.fr        #
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
		builtin/cd_utils.c \
		builtin/pwd.c \
		builtin/env.c \
		builtin/history.c \
		builtin/export.c \
		builtin/unset.c \
		builtin/exit.c \
		\
		parsing/lexer/upgrade_input.c \
		parsing/lexer/env_var.c \
		parsing/lexer/env_var_fill.c \
		parsing/lexer/env_var_length.c \
		parsing/lexer/env_var_utils.c \
		parsing/lexer/pid_value.c \
		parsing/lexer/ret_value.c \
		parsing/lexer/options.c \
		parsing/lexer/option_echo.c \
		parsing/lexer/options_utils.c \
		parsing/lexer/utils.c \
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
		parsing/parser/fill_options.c \
		parsing/parser/fill_args.c \
		parsing/parser/pipes.c \
		parsing/parser/parentheses.c \
		\
		parsing/redirection/parse.c \
		parsing/redirection/files.c \
		parsing/redirection/start_redir.c \
		\
		parsing/heredoc/heredoc.c \
		parsing/heredoc/ctrl_keys_heredoc.c \
		parsing/heredoc/input.c \
		parsing/heredoc/env_var.c \
		parsing/heredoc/special_value.c \
		\
		parsing/checker/input.c \
		parsing/checker/argv.c \
		parsing/checker/argv_utils.c \
		parsing/checker/delimiters_1.c \
		parsing/checker/delimiters_2.c \
		parsing/checker/delimiters_3.c \
		parsing/checker/error_msg.c \
		parsing/checker/unclosed_char.c \
		\
		parsing/utils/paths.c \
		parsing/utils/linked_list.c \
		parsing/utils/print_list.c \
		parsing/utils/exit_error.c \
		parsing/utils/exit_error_2.c \
		parsing/utils/secured.c \
		\
		parsing/parse_exec/reparse.c \
		parsing/parse_exec/refill.c \
		parsing/parse_exec/recheck.c \
		parsing/parse_exec/utils.c \
		\
		env/edit.c \
		env/create.c \
		env/list.c \
		env/utils.c \
		env/print.c \
		\
		exec/exec.c \
		exec/utils.c \
		exec/open_files.c \
		exec/error_files.c \
		exec/bin_cmd.c \
		exec/cmd_array.c \
		exec/builtin_cmd.c \
		exec/pipes.c \
		exec/pipes_utils.c \
		exec/close_fd.c \
		exec/wildcard.c \
		\
		exec/parentheses/exec.c \
		exec/parentheses/check.c \
		exec/parentheses/redir.c \
		exec/parentheses/utils.c \
		\
		shell/init/init.c \
		shell/init/raw.c \
		\
		shell/input/insert_char.c \
		shell/input/erase_char.c \
		\
		shell/keys/arrows.c \
		shell/keys/ctrl_keys.c \
		shell/keys/erase_keys.c \
		shell/keys/read.c \
		shell/keys/tab.c \
		\
		shell/history.c \
		shell/display.c \
		shell/error_msg.c \
		shell/exit.c \
		shell/shell.c \
		shell/signal.c \
		shell/utils.c \
		\
		utils/utils.c \
		utils/utils_2.c \
		utils/free.c \
		utils/init.c \
		utils/clean.c \
		utils/clean_2.c \
		utils/exit_error.c \
		utils/secured_functions_1.c \
		utils/secured_functions_2.c \
		utils/secured_functions_3.c

### COMPILATION ###
CC		= clang
CFLAGS	= -Wall -Wextra -Werror -MMD -MP -I$(INCLUDE)
DEBUG_F	= -g3 -fsanitize=address
LIBS	= -lft -lncurses -lreadline

### INCLUDES ###
INCLUDE		= inc
LIBFT_PATH	= libft
SRC_PATH	= src
OBJ_PATH	= obj

### OBJECTS ###
SRC	= $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJ	= $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))
DEP	= $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.d))

### COLORS ###
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### RULES ###


all: libs
	@make -s $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -L $(LIBFT_PATH) -o $@ $^ $(LIBS)
	@echo "$(GREEN)$@$(NOC)"

-include $(DEP)
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDE)/$(NAME).h
	@mkdir -p obj/builtin obj/env obj/exec obj/exec/parentheses obj/utils
	@mkdir -p obj/parsing/split obj/parsing/checker obj/parsing/heredoc
	@mkdir -p obj/parsing/utils obj/parsing/parser obj/parsing/lexer obj/parsing/parse_exec
	@mkdir -p obj/parsing/redirection obj/shell/init obj/shell/input obj/shell/keys
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(BLUE)clang $(NOC)$(notdir $@)"

libs:
	@make -sC libft

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

.PHONY:	all clean fclean re debug norm push libs
