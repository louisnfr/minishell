#include "minishell.h"

int	get_count_ret_value(char *input)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (input[++i])
	{
		if (input[i] && input[i] == '$')
		{
			i++;
			if (input[i] && input[i] == '?')
				count++;
		}
	}
	return (count);
}

static void	handle_double_quotes(int *i, char *input, t_data *data)
{
	(*i)++;
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] && input[*i] == '$')
		{
			(*i)++;
			if (input[*i] && input[*i] == '?')
				data->simple_quotes[(data->i_quotes)++] = FALSE;
		}
		(*i)++;
	}
}

static void	handle_ret_value(int *i, int *simple_quote, char *input, t_data *data)
{
	(*i)++;
	if (input[*i] && input[*i] == '?')
	{
		if (*simple_quote == -1)
			data->simple_quotes[(data->i_quotes)++] = TRUE;
		else
			data->simple_quotes[(data->i_quotes)++] = FALSE;
	}
}

void	fill_recap_quotes(char *input, t_data *data)
{
	int	i;
	int	simple_quote;

	i = -1;
	data->i_quotes = 0;
	simple_quote = 1;
	while (input[++i])
	{
		if (input[i] && input[i] == '\'')
			simple_quote *= -1;
		if (input[i] && input[i] == '\"')
			handle_double_quotes(&i, input, data);
		if (input[i] && input[i] == '$')
			handle_ret_value(&i, &simple_quote, input, data);
	}	
}

t_bool	check_simple_quotes(char *input, t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = get_count_ret_value(input);
	if (!count)
		return (SUCCESS);
	printf("input : %s | count = %d\n", input, count);
	data->simple_quotes = (int *)malloc(sizeof(int) * count);
	if (!data->simple_quotes)
		return (FAIL);
	data->tab_length = count;
	i = -1;
	while (++i < count)
		data->simple_quotes[i] = FALSE;
	fill_recap_quotes(input, data);

//	i = -1;
//	while (++i < data->tab_length)
//		printf("data->simple_quotes[%d] = %d\n", i, data->simple_quotes[i]);
	
	return (SUCCESS);
}
