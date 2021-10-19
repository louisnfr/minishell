#include "minishell.h"

static int	handle_wildcard_character(
	int *i, int *j, char *filename, char *wildcard)
{
	int	tmp;

	if (!wildcard[*j])
		return (1);
	while (1)
	{
		tmp = *j;
		while (filename[*i] && wildcard[tmp] && filename[*i] != wildcard[tmp])
			(*i)++;
		while (filename[*i] && wildcard[tmp] && filename[*i] == wildcard[tmp])
		{
			(*i)++;
			tmp++;
		}
		if (!wildcard[tmp] && !filename[*i])
			return (1);
		if (wildcard[tmp] && wildcard[tmp] == '*')
		{
			*j = tmp;
			return (2);
		}
		if (!filename[*i])
			return (0);
	}
	return (-1);
}

static int	handle_other_character(
	int *i, int *j, char *filename, char *wildcard)
{
	while (filename[*i] && wildcard[*j] && filename[*i] == wildcard[*j])
	{
		(*i)++;
		(*j)++;
	}
	if (!wildcard[*j] && !filename[*i])
		return (1);
	if (wildcard[*j] && wildcard[*j] != '*')
		return (0);
	return (-1);
}

int	matching_name(char *filename, char *wildcard)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	while (j < (int)ft_strlen(wildcard))
	{
		if (wildcard[j] && wildcard[j] == '*')
		{
			j++;
			ret = handle_wildcard_character(&i, &j, filename, wildcard);
			if (ret == 0 || ret == 1)
				return (ret);
		}
		else if (wildcard[j] && wildcard[j] != '*')
		{
			ret = handle_other_character(&i, &j, filename, wildcard);
			if (ret >= 0)
				return (ret);
		}
	}
	return (0);
}

t_bool	count_wildcard_arg(int *i, char *wildcard_arg)
{
	DIR				*directory;
	struct dirent	*entity;
	int				i_ref;

	i_ref = *i;
	directory = opendir(".");
	if (!directory)
		return (FAIL);
	entity = readdir(directory);
	while (entity != NULL)
	{
		if (matching_name(entity->d_name, wildcard_arg))
			(*i)++;
		entity = readdir(directory);
	}
	closedir(directory);
	if (*i == i_ref)
	{
		(*i)++;	
		return (FAIL);
	}
	return (SUCCESS);
}

t_bool	fill_wildcard_arg(char **cmd_array, int *i, char *wildcard_arg)
{
	DIR				*directory;
	struct dirent	*entity;
	int				i_ref;

	i_ref = *i;
	directory = opendir(".");
	if (!directory)
		return (FAIL);
	entity = readdir(directory);
	while (entity != NULL)
	{
		if (matching_name(entity->d_name, wildcard_arg))
		{
			cmd_array[*i + 1] = ft_strdup(entity->d_name);
			(*i)++;
		}
		entity = readdir(directory);
	}
	closedir(directory);
	if (*i == i_ref)
	{
		cmd_array[*i + 1] = ft_strdup(wildcard_arg);
		(*i)++;
	}
	return (SUCCESS);
}
