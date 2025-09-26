/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:16:21 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/23 09:24:33 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_parent_builtin(char *cmd_name)
{
	return (ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "exit") == 0);
}

int	setup_pipe(int pipe_fd[2], int is_last)
{
	if (is_last)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	return (0);
}

void	update_fds(int *prev_fd, int pipe_fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}
