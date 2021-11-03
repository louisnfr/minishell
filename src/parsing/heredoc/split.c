#include "minishell.h"

t_bool	handle_heredoc_quotes(int *i, char **str, char **strs)
{
	int		j;
	char	*tmp;
	char	charset;

	while (**str && ft_isspace(**str))
		(*str)++;
	if (!(**str) || (**str && **str != '\'' && **str != '\"'))
		return (SUCCESS);
	charset = **str;
	j = 1;
	tmp = ft_strdup(*str);
	while (tmp[j] && tmp[j] != charset)
		j++;
	free(tmp);
	tmp = NULL;
	strs[++(*i)] = (char *)ft_calloc(1, sizeof(char) * (j + 2));
	if (!strs[*i])
		return (FAIL);
	j = 0;
	strs[*i][j++] = **str;
	(*str)++;
	while (**str)
	{
		strs[*i][j++] = **str;
		(*str)++;
		if (**str && **str == charset)
		{
			strs[*i][j++] = **str;
			break ;
		}
	}
	strs[*i][j] = '\0';
	return (SUCCESS);
}
