#ifndef PARSING_H
# define PARSING_H

# define CHILD  0

typedef int	t_bool;

typedef enum t_boolean
{
	FAIL	= 0,
	SUCCESS = 1,
	LEFT	= 0,
	RIGHT	= 1,
}	t_boolean;

typedef struct s_cmd
{
	char			*command;
	char			**options;
	char			*path;
	t_bool			is_builtin;
	struct s_cmd	*left;
	struct s_cmd	*right;
}			t_cmd;

typedef struct s_data
{
	t_cmd	*cmd_list;
	char	**all_paths;
}	t_data;

int		str_is_equal(const char *s1, const char *s2);
void	clean_free(char **str);
char	*ft_strjoin_and_free(char *s1, char *s2);
char	**get_paths(char **env);
char	*find_cmd_path(char *command, char **all_paths);

#endif
