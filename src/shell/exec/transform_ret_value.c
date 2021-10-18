#include "minishell.h"

t_bool	must_be_transformed(char *arg, t_data *data)
{
	int	count;
	int	ret;

	ret = FAIL;
	count = get_count_ret_value(arg);
	if (!count || !data->simple_quotes || data->i_quotes >= data->tab_length)
		return (FAIL);
	printf("data->simple_quotes[%d] = %d\n", data->i_quotes, data->simple_quotes[data->i_quotes]);
	if (!data->simple_quotes[data->i_quotes])
		ret = SUCCESS;
	data->i_quotes += count;
	return (ret);
}
