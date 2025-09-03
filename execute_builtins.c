/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:25:42 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/01 10:25:52 by lpalomin         ###   ########.fr       */
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

int	execute_builtin(t_cmd *cmd, char **envp)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd, envp));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd, envp));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(envp));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd));
	return (-1);
}
