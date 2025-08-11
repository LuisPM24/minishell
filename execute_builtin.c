/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:25:06 by marco             #+#    #+#             */
/*   Updated: 2025/08/11 18:34:33 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(t_cmd *cmd, char **envp)
{
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return (execute_cd(cmd, envp), 1);
    else if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return (execute_echo(cmd, envp), 1);
    /*else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return (execute_pwd(cmd, envp), 1);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        return (execute_export(cmd, envp), 1);
    else if (ft_strcmp(cmd->argv[1], "unset") == 0)
        return (execute_unset(cmd, envp), 1);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        return (execute_env(cmd, envp), 1);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return (execute_exit(cmd, envp), 1);*/
    return (0);
}