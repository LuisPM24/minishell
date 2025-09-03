/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:23:48 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/05 10:50:04 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pipe_argv(t_cmd *cmd)
{
	int	count1;
	int	count2;

	if (!cmd->pipe_argv)
		return ;
	count1 = 0;
	while (cmd->pipe_argv[count1])
	{
		count2 = 0;
		while (cmd->pipe_argv[count1][count2])
			free(cmd->pipe_argv[count1][count2++]);
		free(cmd->pipe_argv[count1]);
		count1++;
	}
	free(cmd->pipe_argv);
	cmd->pipe_argv = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	int	count;

	if (!cmd)
		return ;
	count = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			free(cmd->argv[count++]);
		free(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->pipe_argv)
		free_pipe_argv(cmd);
	if (cmd->redirs)
	{
		free_all_redirs(cmd);
		cmd->redirs = NULL;
	}
}

void	free_split(char **split)
{
	int	count;

	if (!split)
		return ;
	count = 0;
	while (split[count])
	{
		free(split[count]);
		count++;
	}
	free(split);
}

void	free_execve(t_cmd *cmd, char *cmd_path)
{
	free_cmd(cmd);
	free(cmd_path);
	perror("minishell");
	exit(EXIT_FAILURE);
}

void	free_dollar_line(char *full_var, char *dollar_value,
			char *prefix, char *suffix)
{
	if (full_var)
		free(full_var);
	if (dollar_value)
		free(dollar_value);
	if (prefix)
		free(prefix);
	if (suffix)
		free(suffix);
}
