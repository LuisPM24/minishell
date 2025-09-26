/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:58:43 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/22 20:30:27 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_pipe_fds(int *fds)
{
	if (fds[0] != -1)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
}

static void	check_and_apply_redirs(t_cmd *cmd, int pipe_cmd)
{
	if (pipe_cmd < cmd->amount_cmd && cmd->redirs)
		handle_redirections(cmd->redirs[pipe_cmd]);
	if (!cmd->pipe_argv[pipe_cmd] || !cmd->pipe_argv[pipe_cmd][0])
	{
		ft_putstr_fd("minishell: empty command\n", 2);
		exit(127);
	}
}

static void	pipe_error_selector(char *path)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	perror(path);
	exit(126);
}

static void	exec_command_pipe(t_cmd *cmd, char **envp, int pipe_cmd)
{
	char	*cmd_path;

	cmd_path = find_command_path(cmd->pipe_argv[pipe_cmd][0], envp);
	if (!cmd_path || access(cmd_path, F_OK) != 0 || access(cmd_path, X_OK) != 0)
		pipe_error_selector(cmd_path);
	execve(cmd_path, cmd->pipe_argv[pipe_cmd], envp);
	pipe_error_selector(cmd_path);
}

int	fork_and_exec(t_cmd *cmd, char **envp, int pipe_cmd, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_IGN);
		apply_pipe_fds(fds);
		if (cmd->cur_pipe_read != -1 && cmd->cur_pipe_read != fds[0])
			close(cmd->cur_pipe_read);
		if (cmd->cur_pipe_write != -1 && cmd->cur_pipe_write != fds[1])
			close(cmd->cur_pipe_write);
		check_and_apply_redirs(cmd, pipe_cmd);
		if (is_builtin(cmd->pipe_argv[pipe_cmd][0]))
			exit(execute_builtin(cmd, envp, pipe_cmd));
		exec_command_pipe(cmd, envp, pipe_cmd);
	}
	return (pid);
}
