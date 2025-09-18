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

int	check_unclosed_quotes(char *line)
{
	char	aux_char;
	int		count;
	int		inside;
	int		amount;

	aux_char = '\0';
	count = 0;
	inside = 0;
	amount = 0;
	while (line[count])
	{
		if ((line[count] == '"' || line[count] == '\'') && !inside)
		{
			amount++;
			inside = 1;
			aux_char = line[count];
		}
		else if (inside && line[count] == aux_char)
		{
			amount++;
			inside = 0;
			aux_char = '\0';
		}
		count++;
	}
	if (amount % 2 == 0)
		return (1);
	else
		return (0);
}
