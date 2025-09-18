/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:26:07 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/18 17:52:50 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd *cmd, int pipe_cmd)
{
	int	count;
	int	no_newline;

	count = 1;
	no_newline = 0;
	if (!cmd->pipe_argv[pipe_cmd] || !cmd->pipe_argv[pipe_cmd][0])
		return (1);
	if (cmd->pipe_argv[pipe_cmd][count] &&
		ft_strncmp(cmd->pipe_argv[pipe_cmd][count], "-n", 2) == 0)
	{
		no_newline = 1;
		count++;
	}
	while (cmd->pipe_argv[pipe_cmd][count])
	{
		ft_putstr_fd(cmd->pipe_argv[pipe_cmd][count], STDOUT_FILENO);
		if (cmd->pipe_argv[pipe_cmd][count + 1])
			write(STDOUT_FILENO, " ", 1);
		count++;
	}
	if (!no_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	builtin_cd(t_cmd *cmd, int pipe_cmd)
{
	char	**argv;

	argv = cmd->pipe_argv[pipe_cmd];
	if (!argv[1])
	{
		ft_putstr_fd("minishell: cd: missing argument\n", STDERR_FILENO);
		g_exit_status = 1;
		return (1);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	builtin_pwd(char **envp)
{
	char	cwd[PATH_MAX];
	int		i;
	char	**split;

	i = 0;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		while (envp[i] && ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
			i++;
		if (!envp[i])
		{
			ft_putstr_fd("minishell: pwd: OLDPWD not found\n", STDERR_FILENO);
			return (1);
		}
		split = ft_split(envp[i], '=');
		ft_putstr_fd(split[1], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		free_split(split);
		return (0);
	}
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

int	builtin_exit(t_cmd *cmd, int pipe_cmd)
{
	char	**argv;
	int		i;

	if (!cmd->pipe_argv[pipe_cmd] || !cmd->pipe_argv[pipe_cmd][0])
		exit(g_exit_status);
	argv = cmd->pipe_argv[pipe_cmd];
	if (argv[1])
	{
		i = 0;
		if (argv[1][i] == '-' || argv[1][i] == '+')
			i++;
		while (argv[1][i] && ft_isdigit(argv[1][i]))
			i++;
		if (argv[1][i] != '\0')
		{
			perror("minishell: exit: numeric argument required");
			exit(2);
		}
		if (argv[2])
			return (ft_putstr_fd("minishell: exit: too many arguments"
					, STDERR_FILENO), 1);
		exit(ft_atoi(argv[1]) % 256);
	}
	exit(g_exit_status);
}
