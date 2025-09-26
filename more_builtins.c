/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:47:54 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/26 15:48:26 by lpalomin         ###   ########.fr       */
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
	if (cmd->pipe_argv[pipe_cmd][count]
		&& ft_strncmp(cmd->pipe_argv[pipe_cmd][count], "-n", 2) == 0)
	{
		no_newline = 1;
		count++;
	}
	while (cmd->pipe_argv[pipe_cmd][count])
	{
		safe_write(STDOUT_FILENO, cmd->pipe_argv[pipe_cmd][count],
			ft_strlen(cmd->pipe_argv[pipe_cmd][count]));
		if (cmd->pipe_argv[pipe_cmd][count + 1])
			safe_write(STDOUT_FILENO, " ", 1);
		count++;
	}
	if (!no_newline)
		safe_write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	builtin_cd(t_cmd *cmd, int pipe_cmd)
{
	char	**argv;

	argv = cmd->pipe_argv[pipe_cmd];
	if (!argv[1])
	{
		ft_putstr_fd("minishell: cd: missing argument\n", STDERR_FILENO);
		cmd->exit_status = 1;
		return (1);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		cmd->exit_status = 1;
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		cmd->exit_status = 1;
		return (1);
	}
	return (0);
}
