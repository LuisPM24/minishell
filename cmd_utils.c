/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:03:55 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/16 21:14:42 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
	{
		ft_printf("Pos: %i || Cont: %s\n", count, argv[count]);
		count++;
	}
}

void	modify_status(char character, int *status)
{
	if (character == '\'' && (*status) == 0)
		(*status) = 1;
	else if (character == '"' && (*status) == 0)
		(*status) = 2;
	else if ((character == '\'' && (*status) == 1)
		|| (character == '"' && (*status) == 2))
		(*status) = 0;
}

void	add_to_cmd(t_cmd *cmd, char *new_line, int *count2)
{
	if (!cmd || !new_line || *count2 == 0)
		return ;
	new_line[*count2] = '\0';
	cmd->argv[cmd->amount_cmd] = ft_strdup(new_line);
	cmd->amount_cmd++;
	ft_memset(new_line, 0, ft_strlen(new_line) + 1);
	*count2 = 0;
}
