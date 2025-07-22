/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:29:07 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/22 12:48:37 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	check_unclosed_quotes(char *line)
{
	int	count;
	int	simple_quotes;
	int	double_quotes;

	count = 0;
	simple_quotes = 0;
	double_quotes = 0;
	while (line[count])
	{
		if (line[count] == '\'')
			simple_quotes++;
		if (line[count] == '"')
			double_quotes++;
		count++;
	}
	if (simple_quotes % 2 == 0 && double_quotes % 2 == 0)
		return (1);
	else
		return (0);
}
