#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "dirent.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!*s && !c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		d;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i + 1 < n)
		i++;
	d = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (!d || !n)
		return (0);
	else if (d < 0)
		return (-1);
	else
		return (1);
}

int	str_is_equal(const char *s1, const char *s2)
{
	return (!ft_strncmp(s1, s2, ft_strlen(s1))
		&& !ft_strncmp(s1, s2, ft_strlen(s2)));
}

////////////////////////////////////////////////

/*
int	name_matches(char *filename, char *wildcard)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (j < (int)ft_strlen(wildcard))
	{
		if (wildcard[j] && wildcard[j] == '*')
		{
			j++;
			if (!wildcard[j])
				return (1);
			while (1)
			{
				tmp = j;
				while (filename[i] && wildcard[tmp] && filename[i] != wildcard[tmp])
					i++;
				while (filename[i] && wildcard[tmp] && filename[i] == wildcard[tmp])
				{
					i++;
					tmp++;
				}
				if (!wildcard[tmp] && !filename[i])
					return (1);
				if (wildcard[tmp] && wildcard[tmp] == '*')
				{
					j = tmp;
					break ;
				}
				if (!filename[i])
					return (0);
			}
		}
		else if (wildcard[j] && wildcard[j] != '*')
		{
			while (filename[i] && wildcard[j] && filename[i] == wildcard[j])
			{
				i++;
				j++;
			}
			if (!wildcard[j] && !filename[i])
				return (1);
			if (wildcard[j] && wildcard[j] != '*')
				return (0);
		}
	}
	return (0);
}
*/

static int	handle_wildcard_character(int *i, int *j, char *filename, char *wildcard)
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

static int	handle_other_character(int *i, int *j, char *filename, char *wildcard)
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
			ret = handle_other_character(&i, &j, filename, wildcard);;
			if (ret >= 0)
				return (ret);
		}
	}
	return (0);
}

char	*find_matching_files(char *dir_name, char *wildcard)
{
	DIR				*directory;
	struct dirent	*entity;

	(void)wildcard;
	directory = opendir(dir_name);
	if (!directory)
		return (0);
	entity = readdir(directory);
	while (entity != NULL)
	{
		if (matching_name(entity->d_name, wildcard))
		{
			printf("%s\n", entity->d_name);
			return (entity->d_name);
		}
		entity = readdir(directory);
	}
	closedir(directory);
	return (NULL);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argv[1] && ft_strchr(argv[1], '*'))
		find_matching_files(".", argv[1]);
	return (0);
}