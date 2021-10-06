#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/////////////////////////////////////


int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = dst;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

void	free_env(t_env *g_env)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		g_env = g_env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
		tmp = g_env;
	}
	free(g_env);
	g_env = NULL;
}

void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
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


t_env	*new_var(char *key, char *value)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = malloc(sizeof(char) + (ft_strlen(key) + 1));
	var->value = malloc(sizeof(char) + (ft_strlen(value) + 1));
	if (!var->key || !var->value)
		return (NULL);
	ft_memcpy(var->key, key, ft_strlen(key) + 1);
	ft_memcpy(var->value, value, ft_strlen(value) + 1);
	var->next = NULL;
	return (var);
}

t_env	*get_last(t_env *g_env)
{
	if (!g_env)
		return (NULL);
	while (g_env->next)
		g_env = g_env->next;
	return (g_env);
}

void	add_var(t_env **g_env, t_env *new_var)
{
	t_env	*last;

	if (!*g_env)
		*g_env = new_var;
	else
	{
		last = get_last(*g_env);
		last->next = new_var;
	}
}

t_env	*create_env(char **envp)
{
	t_env	*g_env;
	char	**var;
	int		i;

	g_env = NULL;
	i = -1;
	while (envp[++i])
	{
		var = ft_split_on_first(envp[i], '=');
		add_var(&g_env, new_var(var[0], var[1]));
		free_split(var);
	}
	return (g_env);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	dst = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	*check_comment(char *input)
{
	char	*new_input;
	int		length;
	int		i;

	length = -1;
	new_input = NULL;
	while (input[++length])
	{
		while (input[length] && ft_isspace(input[length]))
			length++;
		if (input[length] == '#')
			break ;
		while (input[length] && !ft_isspace(input[length]))
		{
			if (input[length] == '\"')
			{
				length++;
				while (input[length] && input[length] != '\"')
					length++;
			}
			else if (input[length] == '\'')
			{
				length++;
				while (input[length] && input[length] != '\'')
					length++;
			}
			length++;
		}
	}
	if (length == (int)ft_strlen(input))
		return (input);
	new_input = (char *)malloc(sizeof(char) * (length + 1));
	if (!new_input)
		return (NULL);
	i = -1;
	while (++i < length)
		new_input[i] = input[i];
	new_input[i] = '\0';
	free(input);
	return (new_input);
}

int	check_unclosed_quotes(char *input, char quote)
{
	int	i;

	i = -1;
	while (input && input[++i])
	{
		if (input[i] == quote)
		{
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i])
				continue ;
			printf("bash: syntax error: missing quote `%c'\n", quote);
			return (0);
		}
	}
	return (1);
}


char	*get_env(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
static int	get_length(char *str, t_env *env)
{
	int		i;
	int		length;
	char	*env_var;

	i = 0;
	if (!str || !str[i])
		return (0);
	length = 0;
	env_var = NULL;
	while (str && str[i + 1])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			length++;
			while (str[i] && str[i] != '\'')
			{
				i++;
				length++;
			}	
			if (!str[i + 1])
				length--;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
		{
			i += 2;
			if (str[i])
				length += 2;
			else
				length++;
			continue;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && !is_charset(str[i + 1]))
		{
			env_var = get_env_variable(str, &i);
			printf("i = %d | length_env_var : %d\n", i, get_length_env_var(env_var, env));
			length += get_length_env_var(env_var, env);
		//	printf("length_env_variable : %d\n", get_length_env_var(env_var, env));
			free(env_var);
			env_var = NULL;
			if (!str[i])
				length--;
		}
		else
		{
			i++;
			length++;
		}
	}
	length++;
	return (length);
}
*/


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

static int	is_charset(char c)
{
	return (c == ' ' || c == '$' || c == '?' || c == '#' || c == '\'' || c == '\"');
}

int	get_length_env_var(char *env_var, t_env *env)
{
	char	*ret;

	ret = NULL;
	ret = get_env(env_var, env);
	if (ret)
		return (ft_strlen(ret));
	return (0);
}

char	*get_key_variable(char *str, int *i)
{
	char	*env_var;
	int		var_length;
	int		j;

	j = *i + 1;
	var_length = 0;
	env_var = NULL;
	while (str && !is_charset(str[j++]))
		var_length++;
	if (var_length)
	{
		env_var = NULL;
		env_var = (char *)malloc(sizeof(char) * (var_length + 1));
		if (!env_var)
			return (NULL);
		var_length = 0;
		while (str && str[++(*i)] && !is_charset(str[*i]))
			env_var[var_length++] = str[*i];
		env_var[var_length] = '\0';
		printf("env_var = %s\n", env_var);
	}
	return(env_var);
}

void	handle_simple_quotes(int *i, int *length, char *str)
{
	(*i)++;
	(*length)++;
	while (str[*i] && str[*i] != '\'')
	{
		(*i)++;
		(*length)++;
	}	
	if (!str[*i + 1])
		(*length)--;
}

void	handle_double_dollars(int *i, int *length, char *str)
{
	(*i) += 2;
	if (str[*i])
		(*length) += 2;
	else
		(*length)++;
}

void	handle_env_variable(int *i, int *length, char *str, t_env *env)
{
	char	*env_var;

	env_var = NULL;
	env_var = get_key_variable(str, &(*i));
	(*length) += get_length_env_var(env_var, env);
	free(env_var);
	env_var = NULL;
	if (!str[*i])
		(*length)--;
}

static int	get_length(char *str, t_env *env)
{
	int		i;
	int		length;

	i = 0;
	if (!str || !str[i])
		return (0);
	length = 0;
	while (str && str[i + 1])
	{
		if (str[i] && str[i] == '\'')
			handle_simple_quotes(&i, &length, str);
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
		{
			handle_double_dollars(&i, &length, str);
			continue;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && !is_charset(str[i + 1]))
			handle_env_variable(&i, &length, str, env);
		else
		{
			i++;
			length++;
		}
	}
	return (++length);
}

 //*********************************************************

void	fill_simple_quotes(char *new_str, char *str, int *i, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		new_str[*j] = str[*i];
		(*i)++;
		(*j)++;
	}	
}

void	fill_double_dollars(char *new_str, char *str, int *i, int *j)
{
	while (str[*i] && str[*i] == '$')
	{
		new_str[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
}

void	fill_env_var(char *new_str, char *str, int *i, int *j, t_env *env)
{
	int		k;
	char	*key;
	char	*value;

	k = 0;
	key = NULL;
	value = NULL;
	key = get_key_variable(str, &(*i));
	value = get_env(key, env);
	while (value[k])
		new_str[(*j)++] = value[k++];
	free(key);
	key = NULL;
	free(value);
	value = NULL;
}

static int	fill_new_str(char *new_str, char *str, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !str[i])
		return (0);
	while (str && str[i + 1])
	{
		if (str[i] && str[i] == '\'')
		{
			fill_simple_quotes(new_str, str, &i, &j);
		}
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
		{
			fill_double_dollars(new_str, str, &i, &j);
			continue;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && !is_charset(str[i + 1]))
		{
			fill_env_var(&(*new_str), str, &i, &j, env);
		}
		else
		{
			new_str[j++] = str[i++];
		}
	}
	return (1);
}


char	*check_env_variable(char *input, t_env *env)
{
	char	*new_str;
	int		length;

	new_str = NULL;
	length = get_length(input, env);
	printf("length = %d\n", length);
	new_str = (char *)malloc(sizeof(char) * (length + 1));
	if (!new_str)
		return (NULL);
	fill_new_str(new_str, input, env);
	free(input);
	input = NULL;
	return (new_str);
}

void	fonction(void)
{
	system("leaks a.out");
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;

	env = NULL;
	if (argc != 2)
		return (1);
	input = ft_strdup(argv[1]);
	printf("\nInput : |%s|\n", input);
	input = check_comment(input);
	if (!check_unclosed_quotes(input, '\"'))
		return (1);
	if (!check_unclosed_quotes(input, '\''))
		return (1);
	printf("\nInput : |%s|\n\n", input);
	env = create_env(envp);

	input = check_env_variable(input, env);
	printf("input = %s\n", input);

	free_env(env);
	free(input);
	input = NULL;
//	atexit(fonction);
	return (0);
}
