/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:46:04 by marco             #+#    #+#             */
/*   Updated: 2025/08/24 16:57:02 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **update_envp(char **envp, char *str)
{
    char **new_envp;
    int i;
    
    i = 0;
    while (envp[i])
        i++;
    new_envp = ft_calloc(i + 2, sizeof(char *));
    i = 0;
    while (envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
        i++;
    }
    new_envp[i] = ft_strdup(str);
    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free (envp);
    return (new_envp);
}

static int check_exist(char *str, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0 && envp[i][ft_strlen(str)] == '=')
            return (i);
        i++;
    }
    return (-1);
}

char    **execute_export(t_cmd *cmd, char **envp)
{
    char **str;
    int location;
    int i;

    if (cmd->argv[1] == NULL)
        return (envp);
    str = ft_split(cmd->argv[1], '=');
    location = check_exist(str[0], envp);
    i = 0;
    if (location == -1)
        envp = update_envp(envp, cmd->argv[1]);
    else
    {
        free (envp[location]);
        envp[location] = ft_strdup(cmd->argv[1]);
    }
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
    return (envp);
}
