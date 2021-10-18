#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

#define TRUE	1
#define FALSE	0

typedef struct s_data
{
	int	*recap_quotes;
}	t_data;

int	get_count(char *input)
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

static void	handle_double_quotes()
{

}

void	fill_recap_quotes(char *input, t_data *data)
{
	int	i;
	int	j;
	int	simple_quote;

	i = -1;
	j = 0;
	simple_quote = 1;
	while (input[++i])
	{
		if (input[i] && input[i] == '\'')
			simple_quote *= -1;
		if (input[i] && input[i] == '\"')
			handle_double_quotes(&i, &j, char *input, t_data *data);
		{
			i++;
			while (input[i] && input[i] != '\"')
			{
				if (input[i] && input[i] == '$')
				{
					i++;
					if (input[i] && input[i] == '?')
						data->recap_quotes[j++] = FALSE;
				}
				i++;
			}
		}
		if (input[i] && input[i] == '$')
		{
			i++;
			if (input[i] && input[i] == '?')
			{
				if (simple_quote == -1)
					data->recap_quotes[j++] = TRUE;
				else
					data->recap_quotes[j++] = FALSE;
			}
		}
	}	
}

void	check_argv(char *input, t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = get_count(input);
	if (!count)
		return ;
	printf("Count = %d\n", count);
	data->recap_quotes = (int *)malloc(sizeof(int) * count);
	i = -1;
	while (++i < count)
		data->recap_quotes[i] = FALSE;
	fill_recap_quotes(input, data);
	i = -1;
	while (++i < count)
		printf("data->recap_quotes[%d] = %d\n", i, data->recap_quotes[i]);
}

int	main(int argc, char **argv)
{
	t_data *data;

	(void)argc;
	if (!argv[1])
		return (0);
	data = malloc(sizeof(t_data));
	check_argv(argv[1], data);
	return (0);
}
