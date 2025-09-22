/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:41:46 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/19 09:29:06 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_children(int amount_cmd, pid_t last_pid)
{
	int		count;
	int		status;
	pid_t	pid;

	count = 0;
	while (count < amount_cmd)
	{
		pid = wait(&status);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		count++;
	}
}

static int	count_pipe_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd->pipe_argv[count])
		count++;
	return (count);
}

static pid_t	exec_one_pipe(t_cmd *cmd, char **envp,
							int pipe_cmd, int *prev_fd)
{
	int		pipe_fd[2];
	int		fds[2];
	int		is_last;
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	is_last = (pipe_cmd == cmd->amount_cmd - 1);
	setup_pipe(pipe_fd, is_last);
	fds[0] = *prev_fd;
	fds[1] = pipe_fd[1];
	if (cmd->amount_cmd == 1 && is_builtin(cmd->pipe_argv[pipe_cmd][0])
		&& is_parent_builtin(cmd->pipe_argv[pipe_cmd][0]))
	{
		g_exit_status = execute_builtin(cmd, envp, pipe_cmd);
		update_fds(prev_fd, pipe_fd);
		return (-1);
	}
	cmd->cur_pipe_read = pipe_fd[0];
	cmd->cur_pipe_write = pipe_fd[1];
	pid = fork_and_exec(cmd, envp, pipe_cmd, fds);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
	return (pid);
}


void	execute_pipes(t_cmd *cmd, char **envp)
{
	int		pipe_cmd;
	int		prev_fd;
	pid_t	last_pid;

	prev_fd = -1;
	cmd->amount_cmd = count_pipe_cmds(cmd);
	pipe_cmd = 0;
	last_pid = -1;
	while (pipe_cmd < cmd->amount_cmd)
	{
		last_pid = exec_one_pipe(cmd, envp, pipe_cmd, &prev_fd);
		pipe_cmd++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	if (last_pid != -1)
		wait_for_children(cmd->amount_cmd, last_pid);
}
