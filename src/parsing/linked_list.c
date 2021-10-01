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
			i = -1;
			while (tmp->options[++i])
				printf("Option[%d] : %s\t", i, tmp->options[i]);
			printf("\n");
		}
		if (tmp->args)
		{
			i = -1;
			while (tmp->args[++i])
				printf("Arg[%d] : %s\t", i, tmp->args[i]);
			printf("\n");
		}
		if (tmp->path)
			printf("Path : %s\n", tmp->path);
		tmp = tmp->left;
		printf("\n");
	}
}

void	remove_from_list(t_cmd *cmd_list)
{
	cmd_list->is_builtin = 0;
	clean_free(&cmd_list->command);
	if (cmd_list->options)
	{	
		free(cmd_list->options);
		cmd_list->options = NULL;
	}
	if (cmd_list->args)
	{	
		free(cmd_list->args);
		cmd_list->args = NULL;
	}
	clean_free(&cmd_list->path);
	free(cmd_list);
	cmd_list = NULL;
}

void	clean_cmd_list(t_cmd *cmd_list)
{
	while (cmd_list->left)
	{
		remove_from_list(cmd_list);
		cmd_list = cmd_list->left;
	}
	cmd_list = NULL;
}

t_bool	create_new_cmd(char *cmd, char **options, char *path, t_cmd **cmd_list)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (FAIL);
	setup_cmd_list(new_cmd);
	if (cmd)
		new_cmd->command = ft_strdup(cmd);
	new_cmd->options = options;
	if (path)
		new_cmd->path = ft_strdup(path);
	new_cmd->is_builtin = FALSE;
	new_cmd->left = NULL;
	new_cmd->right = NULL;
	while ((*cmd_list)->left)
		(*cmd_list) = (*cmd_list)->left;
	(*cmd_list)->left = new_cmd;
	(*cmd_list) = (*cmd_list)->left;
	return (SUCCESS);
}

void	setup_cmd_list(t_cmd *cmd_list)
{
	cmd_list->command = NULL;
	cmd_list->options = NULL;
	cmd_list->args = NULL;
	cmd_list->path = NULL;
	cmd_list->left = NULL;
	cmd_list->right = NULL;
}
