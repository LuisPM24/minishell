/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:40:58 by marco             #+#    #+#             */
/*   Updated: 2025/08/19 14:46:06 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_pwd(t_cmd *cmd, char ** envp)
{
    char **pwd;
    int i;

    i = 0;
    (void)cmd;
    while (ft_strncmp(envp[i], "PWD=", 4) != 0)
        i++;
    pwd = ft_split(envp[i], '=');
    ft_printf("%s\n", pwd[1]);
    return ;
}