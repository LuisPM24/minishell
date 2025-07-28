/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:19:48 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/24 11:04:02 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_char(char *line, char remove)
{
	char	*new_line;
	int		count1;
	int		count2;

	count1 = 0;
	count2 = 0;
	if (!line)
		return (NULL);
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	while (line[count1])
	{
		if (line[count1] != remove)
		{
			new_line[count2] = line[count1];
			count2++;
		}
		count1++;
	}
	new_line[count2] = '\0';
	return (new_line);
}
