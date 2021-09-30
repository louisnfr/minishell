#include "minishell.h"

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
