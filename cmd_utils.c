/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:03:55 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/25 08:38:55 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd && cmd->argv[count])
	{
		printf("Pos: %i || Cont: %s\n", count, cmd->argv[count]);
		count++;
	}
}

void	modify_status(char character, int *status)
{
	//0 -> none; 1 ->single quotes ; 2 ->doble quotes
	if (character == '\'' && (*status) == 0)
		(*status) = 1;
	else if (character == '"' && (*status) == 0)
		(*status) = 2;
	else if ((character == '\'' && (*status) == 1)
		|| (character == '"' && (*status) == 2))
		(*status) = 0;
}

static void	add_to_cmd(t_cmd *cmd, char *new_line, int *count2)
{
	if (!cmd || !new_line || *count2 == 0)
		return ;
	new_line[*count2] = '\0';
	cmd->argv[cmd->amount_cmd] = ft_strdup(new_line);
	cmd->amount_cmd++;
	ft_memset(new_line, 0, ft_strlen(new_line) + 1);
	*count2 = 0;
}

void	parse_line(t_cmd *cmd, char *line)
{
	int		status;
	int		count1;
	int		count2;
	char	*new_line;

	count1 = 0;
	count2 = 0;
	status = 0;
	new_line = malloc(ft_strlen(line) + 1);
	while (line[count1])
	{
		modify_status(line[count1], &status);
		if ((line[count1] == ' ' || line[count1] == '|'
				|| line[count1] == '<' || line[count1] == '>') && status == 0)
		{
			add_to_cmd(cmd, new_line, &count2);
			if (line[count1] != ' ')
			{
				new_line[0] = line[count1];
				new_line[1] = '\0';
				cmd->argv[cmd->amount_cmd++] = ft_strdup(new_line);
			}
		}
		else
			new_line[count2++] = line[count1];
		count1++;
	}
	if (count2 > 0)
		add_to_cmd(cmd, new_line, &count2);
	free(new_line);
}
