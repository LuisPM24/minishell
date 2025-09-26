/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_full_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:15:46 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/26 16:16:14 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_braced_var(char *line, int count)
{
	int	start;

	start = count;
	while (line[count] && ft_isalnum(line[count]))
		count++;
	if (count == start || line[count] != '}')
		return (-1);
	return (count + 1);
}

static int	handle_plain_var(char *line, int count)
{
	if (!ft_isalnum(line[count]))
		return (-1);
	while (line[count] && ft_isalnum(line[count]))
		count++;
	return (count);
}

char	*extract_full_var(char *line, int position)
{
	int		count;
	int		end;

	if (!line || line[position] != '$')
		return (NULL);
	count = position + 1;
	if (line[count] == '?')
		return (ft_substr(line, position, 2));
	if (!line[count] || !(ft_isalnum(line[count]) || line[count] == '_'))
		return (ft_substr(line, position, 1));
	if (line[count] == '{')
	{
		end = handle_braced_var(line, count + 1);
		if (end == -1)
			return (NULL);
	}
	else
	{
		end = handle_plain_var(line, count);
		if (end == -1)
			return (NULL);
	}
	return (ft_substr(line, position, end - position));
}
