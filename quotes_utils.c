/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:29:07 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/14 09:55:07 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_argv_range(t_cmd *cmd, int cmd_index, int start, int len)
{
	char	**av;
	int		count;

	av = cmd->pipe_argv[cmd_index];
	count = start;
	while (av[count + len])
	{
		free(av[count]);
		av[count] = ft_strdup(av[count + len]);
		count++;
	}
	while (av[count])
	{
		free(av[count]);
		av[count] = NULL;
		count++;
	}
}

static void	cycle(char **line, int *amount)
{
	char	aux_char;
	int		count;
	int		inside;

	aux_char = '\0';
	count = 0;
	inside = 0;
	while ((*line)[count])
	{
		if (((*line)[count] == '"' || (*line)[count] == '\'') && !inside)
		{
			(*amount)++;
			inside = 1;
			aux_char = (*line)[count];
		}
		else if (inside && (*line)[count] == aux_char)
		{
			(*amount)++;
			inside = 0;
			aux_char = '\0';
		}
		count++;
	}
}

int	check_unclosed_quotes(char *line)
{
	int		amount;

	amount = 0;
	cycle(&line, &amount);
	if (amount % 2 == 0)
		return (1);
	else
		return (0);
}
