#include "minishell.h"

void	display_error_message(char *cmd, char *errno_msg, int fd)
{
	ft_putstr_fd("bash: ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(errno_msg, fd);
	ft_putchar_fd('\n', fd);
}

void	syntax_error_char_msg(int nb, char token)
{
	int	count;

	count = 0;
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	while (count++ < nb)
		ft_putchar_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

char	**syntax_error_str_msg(char *token)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (NULL);
}
