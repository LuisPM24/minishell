/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:59:18 by marco             #+#    #+#             */
/*   Updated: 2025/08/11 18:28:25 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_get_pwd(char **envp)
{
    int i;
    
    i = 0;
    while (ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (envp[i])
        return (envp[i]);
    return (NULL);
}

static char *ft_get_home(char **envp)
{
    char *path;
    char **user;
    int i;

    path = "/home/";
    i = 0;
    while (ft_strncmp(envp[i], "USER=", 5) != 0)
        i++;
    if (!envp[i])
        return NULL;
    user = ft_split(envp[i], '='); 
    path = ft_strjoin(path, user[1]);
    return path;
}

void execute_cd(t_cmd *cmd, char **envp)
{
    char *pwd;

    pwd = ft_get_pwd(envp);
    if (!pwd)
        return (perror("cd"));
    if (cmd->amount_cmd < 2 || !cmd->argv[1])
    {
        if (chdir(ft_get_home(envp)) == -1)
            return (perror("cd"));
    }
    else
    {
        if (chdir(cmd->argv[1]) == -1)
            return (perror("cd"));
    }
    return ;
}
