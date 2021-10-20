#include "minishell.h"

void	*display_error_msg_simple_dot(void)
{
	ft_putstr_fd("bash: .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	return (NULL);
}

int	display_error_msg_delimiter(int count, char delimiter, t_data *data)
{
	int	i;

	if (count == -1)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (count)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		i = -1;
		while (++i < count)
			ft_putchar_fd(delimiter, 2);
		ft_putstr_fd("'\n", 2);
	}
	data->ret_value = 258;
	return (FAIL);
}
