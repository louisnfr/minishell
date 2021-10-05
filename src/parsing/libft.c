#include "minishell.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	str_is_equal(const char *s1, const char *s2)
{
	return (!ft_strncmp(s1, s2, ft_strlen(s1))
		&& !ft_strncmp(s1, s2, ft_strlen(s2)));
}

void	clean_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	size_t	i;
	size_t	length;
	char	*dest;

	if (!s1)
		return (ft_strdup(s2));
	length = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (length + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (*s2)
		dest[i++] = *s2++;
	dest[i] = '\0';
	clean_free(&s1);
	return (dest);
}

void	free_double_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str && str[++i])
		clean_free(&str[i]);
	free(str);
	str = NULL;
}

static size_t	sizeof_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	return (i);
}

static	char	**free_tab(char **tabc, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(tabc[i++]);
	free(tabc);
	return (0);
}

char	**ft_split_on_first(const char *s, char c)
{
	char	**tabc;
	int		index;
	int		i;

	if (!s)
		return (NULL);
	tabc = malloc(sizeof(char *) * 3);
	if (!tabc)
		return (NULL);
	index = 0;
	tabc[index] = malloc(sizeof(char) * (sizeof_word(s, c) + 1));
	if (!tabc[index])
		return (free_tab(tabc, index));
	i = 0;
	while (*s && (*s != c))
		tabc[index][i++] = *s++;
	tabc[index][i] = 0;
	index++;
	tabc[index] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tabc[index])
		return (free_tab(tabc, index));
	i = 0;
	s++;
	while (*s)
		tabc[index][i++] = *s++;
	tabc[index][i] = 0;
	index++;
	tabc[index] = 0;
	return (tabc);
}
