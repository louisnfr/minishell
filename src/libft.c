#include "minishell.h"

char	**copy_strs_and_free(char **strs, t_data *data)
{
	int		i;
	char	**strs_copy;

	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i])
		i++;
	strs_copy = (char **)ft_calloc(1, sizeof(char *) * (i + 1));
	if (!strs_copy)
		return ((char **)exit_error_void(NULL, "malloc()", data));
	i = -1;
	while (strs[++i])
		strs_copy[i] = safe_strdup(strs[i], data);
	strs_copy[i] = NULL;
	free_double_str(strs);
	return (strs_copy);
}

unsigned long long	ft_atoull(const char *str)
{
	unsigned long long	value;
	size_t				i;

	value = 0;
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		value = value * 10 + str[i++] - 48;
	return (value);
}
