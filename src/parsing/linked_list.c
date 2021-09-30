#include "minishell.h"

void	print_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd_list;
	printf("\n");
	while (tmp)
	{
		printf("Cmd : %s\n", tmp->command);
		printf("Is_builtin : %d\n", tmp->is_builtin);
		if (tmp->options)
		{
			i = 0;
			while (tmp->options[i])
				printf("Options : %s\n", tmp->options[i++]);
		}
		if (tmp->path)
			printf("Path : %s\n", tmp->path);
		tmp = tmp->left;
		printf("\n");
	}
}

t_bool	create_new_cmd(char *cmd, char **options, char *path, t_cmd **cmd_list)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (FAIL);
	new_cmd->command = cmd;
	new_cmd->options = options;
	new_cmd->path = path;
	new_cmd->is_builtin = FALSE;
	new_cmd->left = NULL;
	new_cmd->right = NULL;
	while ((*cmd_list)->left)
		(*cmd_list) = (*cmd_list)->left;
	(*cmd_list)->left = new_cmd;
	(*cmd_list) = (*cmd_list)->left;
	return (SUCCESS);
}

void	init_cmd_list(t_cmd *cmd_list)
{
	cmd_list->command = NULL;
	cmd_list->options = NULL;
	cmd_list->path = NULL;
	cmd_list->left = NULL;
	cmd_list->right = NULL;
}
