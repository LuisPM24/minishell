/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:36:06 by marco             #+#    #+#             */
/*   Updated: 2025/08/24 18:32:21 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **cpy_new_envp(char **envp, int location)
{
    char **new_envp;
    int i;
    int j;

    i = 0;
    while (envp[i])
        i++;
    new_envp = ft_calloc(i, sizeof(char *));
    i = 0;
    j = 0;
    while (envp[i])
    {
        if (i == location)
            i++;
        else
        {
            new_envp[j] = ft_strdup(envp[i]);
            i++;
            j++;
        }
    }
    return (new_envp);
}

static char **unset_envp(char **envp, int location)
{
    int i;
    char **new_envp;

    
    new_envp = cpy_new_envp(envp, location);
    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
    return (new_envp);
}

char **execute_unset(t_cmd *cmd, char **envp)
{
    char **str;
    int location;
    int i;

    i = 0;
    if (cmd->argv == NULL)
        return (envp);
    str = ft_split(cmd->argv[1], '=');
    location = check_exist(str[0], envp);
    if (location == -1)
        return (envp);
    envp = unset_envp(envp, location);
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
    return (envp);
}