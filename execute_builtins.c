/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:25:42 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/10 19:01:35 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	count;

	if (!envp)
		return ;
	count = 0;
	while (envp[count])
	{
		free(envp[count]);
		count++;
	}
	free(envp);
}

void	put_error(const char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

int	is_builtin(char *cmd_name)
{
	return (ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0);
}

int	execute_builtin(t_cmd *cmd, char **envp, int pipe_cmd)
{
	if (ft_strcmp(cmd->pipe_argv[pipe_cmd][0], "echo") == 0)
		return (builtin_echo(cmd, pipe_cmd));
	else if (ft_strcmp(cmd->pipe_argv[pipe_cmd][0], "cd") == 0)
		return (builtin_cd(cmd, pipe_cmd));
	else if (ft_strcmp(cmd->pipe_argv[pipe_cmd][0], "pwd") == 0)
		return (builtin_pwd(envp));
	else if (ft_strcmp(cmd->pipe_argv[pipe_cmd][0], "export") == 0)
		return (builtin_export(cmd, pipe_cmd, envp));
	else if (ft_strcmp(cmd->pipe_argv[pipe_cmd][0], "unset") == 0)
		return (builtin_unset(cmd, pipe_cmd, envp));
	else if (ft_strcmp(cmd->pipe_argv[pipe_cmd][0], "env") == 0)
		return (builtin_env(envp));
	else if (ft_strcmp(cmd->pipe_argv[pipe_cmd][0], "exit") == 0)
		return (builtin_exit(cmd, pipe_cmd));
	return (-1);
}
