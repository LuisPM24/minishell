/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:21:02 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/21 12:19:41 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*form_path(char **paths, char *command)
{
	char	*command_path;
	char	*command_fullpath;
	int		count;

	count = 0;
	while (paths[count])
	{
		command_path = ft_strjoin(paths[count], "/");
		command_fullpath = ft_strjoin(command_path, command);
		free(command_path);
		if (access(command_fullpath, X_OK) == 0)
		{
			free_split(paths);
			return (command_fullpath);
		}
		free(command_fullpath);
		count++;
	}
	free_split(paths);
	return (NULL);
}

static char	*find_command_path(char *command, char **envp)
{
	char	**paths;
	int		count;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	count = 0;
	while (envp[count] && ft_strnstr(envp[count], "PATH", 4) == 0)
		count++;
	if (!envp[count])
		return (NULL);
	paths = ft_split(envp[count] + 5, ':');
	if (!paths)
		return (NULL);
	return (form_path(paths, command));
}

static void	make_fork_and_execve(t_cmd *cmd, char *cmd_path, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return ;
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmd->argv, envp) == -1)
		{
			perror("execve");
			free_execve(cmd, cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
	}
}

void	execute_cmd(t_cmd *cmd, char **envp)
{
	char	*command_path;

	if (!cmd || !cmd->argv)
		return ;
	command_path = find_command_path(cmd->argv[0], envp);
	if (!command_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return ;
	}
	make_fork_and_execve(cmd, command_path, envp);
}
