/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:26:07 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/01 10:26:18 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int	count;
	int	no_newline;

	count = 1;
	no_newline = 0;
	if (cmd->argv[count] && ft_strcmp(cmd->argv[count], "-n") == 0)
	{
		no_newline = 1;
		count++;
	}
	while (cmd->argv[count])
	{
		ft_putstr_fd(cmd->argv[count], STDOUT_FILENO);
		if (cmd->argv[count + 1])
			write(STDOUT_FILENO, " ", 1);
		count++;
	}
	if (!no_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	builtin_cd(t_cmd *cmd)
{
	if (!cmd->argv[1])
		return (ft_putstr_fd("minishell: cd: missing argument\n", STDERR_FILENO)
			, 1);
	if (chdir(cmd->argv[1]) != 0)
		return (perror("cd"), 1);
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("pwd"), 1);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	builtin_env(char **envp)
{
	int	count;

	if (!envp)
		return (1);
	count = 0;
	while (envp[count])
	{
		ft_putendl_fd(envp[count], STDOUT_FILENO);
		count++;
	}
	return (0);
}

int	builtin_exit(t_cmd *cmd)
{
	int	status;

	if (!cmd || !cmd->argv)
		exit(g_exit_status);
	if (cmd->argv[1])
	{
		status = ft_atoi(cmd->argv[1]);
		exit(status);
	}
	exit(g_exit_status);
}
