/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:48:46 by marco             #+#    #+#             */
/*   Updated: 2025/08/19 14:50:53 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_env(t_cmd *cmd, char **envp)
{
    int i;

    i = 0;
    (void)cmd;
    while (envp[i])
    {
        ft_printf("%s\n", envp[i]);
        i++;
    }
    return ;
}