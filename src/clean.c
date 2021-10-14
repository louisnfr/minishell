#include "minishell.h"

void	remove_from_list(t_cmd *cmd_list)
{
	cmd_list->is_builtin = 0;
	clean_free(&cmd_list->command);
	if (cmd_list->options)
		free_double_str(cmd_list->options);
	if (cmd_list->args)
		free_double_str(cmd_list->args);
	clean_free(&cmd_list->path);
	if (cmd_list->heredoc)
	{
		unlink(cmd_list->heredoc);
		clean_free(&cmd_list->heredoc);
		clean_free(&cmd_list->heredoc_delimiter);
	}
	free(cmd_list);
	cmd_list = NULL;
}

void	clean_cmd_list(t_cmd *cmd_list)
{
	while (cmd_list->next)
	{
		remove_from_list(cmd_list);
		cmd_list = cmd_list->next;
	}
	remove_from_list(cmd_list);
	cmd_list = NULL;
}

void	clean_data(t_data *data)
{
	clean_cmd_list(data->cmd_list);
	data->cmd_list = NULL;
	free_env(data->env);
	clean_free(&data->tab_delimiters);
	free_double_str(data->all_paths);
}
