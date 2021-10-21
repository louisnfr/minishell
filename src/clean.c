#include "minishell.h"

void	remove_from_list(t_cmd *cmd_list)
{
	if (!cmd_list)
		return ;
	cmd_list->is_builtin = 0;
	cmd_list->delimiter = 0;
	cmd_list->input = 0;
	cmd_list->output = 1;
	cmd_list->error_output = 2;
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
	t_cmd	*tmp;

	while (cmd_list->next)
	{
		tmp = cmd_list->next;
		remove_from_list(cmd_list);
		cmd_list = tmp;
	}
	remove_from_list(cmd_list);
	cmd_list = NULL;
}

void	clean_data(t_data *data)
{
	data->i = 0;
	data->pid = 0;
	data->ret_value = 0;
	free_double_str(data->all_paths);
	free_double_str(data->envp);
	clean_cmd_list(data->cmd_list);
	data->cmd_list = NULL;
	free_env(data->env);
	clean_free(&data->tab_delimiters);
	clean_free(&data->prpt);
}
