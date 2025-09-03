/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:15:30 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/19 09:27:43 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_cmd *cmd)
{
	int	count;
	int	amount_pipes;

	count = 0;
	amount_pipes = 0;
	while (cmd->argv[count])
	{
		if (ft_strcmp(cmd->argv[count], "|") == 0)
			amount_pipes++;
		count++;
	}
	return (amount_pipes);
}

static void	free_pipe_argv_partial(char ***pipe_argv, int count2)
{
	int	count;

	count = 0;
	while (count < count2)
	{
		free_split(pipe_argv[count]);
		count++;
	}
	free(pipe_argv);
}

static int	copy_command_args(t_cmd *cmd, int start, int len, int count2)
{
	int	count3;

	count3 = 0;
	while (count3 < len)
	{
		cmd->pipe_argv[count2][count3] = ft_strdup(cmd->argv[start + count3]);
		if (!cmd->pipe_argv[count2][count3])
		{
			while (count3 > 0)
			{
				count3--;
				free(cmd->pipe_argv[count2][count3]);
			}
			free(cmd->pipe_argv[count2]);
			return (0);
		}
		count3++;
	}
	cmd->pipe_argv[count2][len] = NULL;
	return (1);
}

static int	build_command(t_cmd *cmd, int *count1, int count2)
{
	int	start;
	int	len;

	start = *count1;
	while (cmd->argv[*count1] && ft_strcmp(cmd->argv[*count1], "|") != 0)
		(*count1)++;
	len = *count1 - start;
	cmd->pipe_argv[count2] = malloc((len + 1) * sizeof(char *));
	if (!cmd->pipe_argv[count2])
		return (0);
	if (len == 0)
		cmd->pipe_argv[count2][0] = NULL;
	else if (!copy_command_args(cmd, start, len, count2))
		return (0);
	if (cmd->argv[*count1] && ft_strcmp(cmd->argv[*count1], "|") == 0)
		(*count1)++;
	return (1);
}

void	parse_pipe_argv(t_cmd *cmd)
{
	int	count1;
	int	count2;
	int	n_cmds;

	count1 = 0;
	count2 = 0;
	n_cmds = count_pipes(cmd) + 1;
	cmd->pipe_argv = malloc((n_cmds + 1) * sizeof(char **));
	if (!cmd->pipe_argv)
		return ;
	while (count2 < n_cmds)
	{
		if (!build_command(cmd, &count1, count2))
		{
			free_pipe_argv_partial(cmd->pipe_argv, count2);
			cmd->pipe_argv = NULL;
			return ;
		}
		count2++;
	}
	cmd->pipe_argv[n_cmds] = NULL;
}
