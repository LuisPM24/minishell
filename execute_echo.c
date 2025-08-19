/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:13:46 by marco             #+#    #+#             */
/*   Updated: 2025/08/19 14:37:22 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_echo(t_cmd *cmd)
{
    int i;
    int new_line;
    
    i = 1;
    new_line = 1;
    if (cmd->argv[i] && ft_strcmp(cmd->argv[i], "-n") == 0)
    {
        new_line = 0;
        i++;
    }
    while (cmd->argv[i])
    {
        printf("%s", cmd->argv[i]);
        i++;
        if (cmd->argv[i])
            printf(" ");
    }
    if (new_line)
        printf("\n");
}

void execute_echo(t_cmd *cmd, char **envp)
{
    (void)envp;
    print_echo(cmd);
}