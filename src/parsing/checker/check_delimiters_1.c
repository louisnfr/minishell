#include "minishell.h"

int	check_multiple_delimiters(char *str, int j, t_data *data)
{
	int		i;
	char	*delimiters;

	delimiters = data->tab_delimiters;
	i = -1;
	while (delimiters[++i])
	{
		if (str[j] && str[j] == delimiters[i]
			&& delimiters[i] != '<' && delimiters[i] != '>')
		{
			if (str[j + 1] && str[j + 1] == delimiters[i])
				return (2);
			return (1);
		}
	}
	if (str[j] == '<')
		return (check_left_marks(str, j));
	if (str[j] == '>')
		return (check_right_marks(str, j));
	return (0);
}

int	check_error_delimiter(int j, char *str, int delimiter, t_data *data)
{
	int		ret;

	while (str[j] && ft_isspace(str[j]))
		j++;
	if (j && str[j] && str[j] == delimiter)
	{
		if (str[j + 1] == delimiter)
			return (display_error_msg_delimiter(2, str[j], data));
		return (display_error_msg_delimiter(1, str[j], data));
	}
	ret = check_multiple_delimiters(str, j, data);
	if ((ret > 0 && ret < 4) || ret == -1)
	{
		if (!is_error_redir(str, j))
			return (display_error_msg_delimiter(ret, str[j], data));
		return (2);
	}
	return (1);
}

int	check_delimiter(char *str, char delimiter, int *i, int *words, t_data *data)
{
	int		count;
	int		j;
	t_bool	is_beginning;
	int		ret;
	
	count = 0;
	if (!str[*i] || (str[*i] && str[*i] != delimiter))
		return (1);
	(*words)++;
	is_beginning = check_beginning(str, i);
	while (str[*i] && str[*i] == delimiter)
	{
		(*i)++;
		count++;
	}
	if ((delimiter == '|' && count == 3 && !is_beginning)
		|| (delimiter == '&' && (count == 1 || count == 3) && !is_beginning) ||
		(delimiter == '>' && count == 3) || (delimiter == '<' && count == 3))
		return (display_error_msg_delimiter(1, delimiter, data));
	if ((delimiter == '|' && count == 3) || (delimiter == '&' && count == 3)
		|| (delimiter == '|' && count > 3) || (delimiter == '&' && count > 3)
		|| (delimiter == ';' && count > 1) || (delimiter == '>' && count > 3)
		|| (delimiter == '<' && count == 4))
		return (display_error_msg_delimiter(2, delimiter, data));
	if (delimiter == '<' && count > 4)
		return (display_error_msg_delimiter(3, delimiter, data));
	j = *i;
	ret = check_error_delimiter(j, str, delimiter, data);
	if (ret == 2)
	{
		(*words)--;
		return (SUCCESS);
	}
	return (ret);
}
