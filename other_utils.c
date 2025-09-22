/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:19:48 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/23 09:31:55 by lpalomin         ###   ########.fr       */
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

char	*remove_last_quotes(char *line)
{
	char	*new_line;
	int		count1;
	int		count2;
	int		status;

	count1 = 0;
	count2 = 0;
	status = 0;
	if (!line)
		return (NULL);
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	if ((line[0] == '"' || line[0] == '\'') && (line[1] == '<' || line[1] == '>'))
	{
		while (line[count1])
		{
			modify_status(line[count1], &status);
			if ((status == 2 && line[count1] != '"') || (status == 1
					&& line[count1] != '\'') || (status == 0
					&& line[count1] != '\'' && line[count1] != '"'))
				new_line[count2++] = line[count1];
			count1++;
		}
	}
	else
		return (free(new_line), ft_strdup(line));
	new_line[count2] = '\0';
	return (new_line);
}

char	*remove_quotes(char *line)
{
	char	*new_line;
	int		count1;
	int		count2;
	int		status;

	count1 = 0;
	count2 = 0;
	status = 0;
	if (!line)
		return (NULL);
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	while (line[count1])
	{
		modify_status(line[count1], &status);
		if (count1 == 0 && status != 0 && (line[count1 + 1] == '<' || line[count1 + 1] == '>'))
			return (free(new_line), ft_strdup(line));
		else if ((status == 2 && line[count1] != '"') || (status == 1
				&& line[count1] != '\'') || (status == 0
				&& line[count1] != '\'' && line[count1] != '"'))
		{
			new_line[count2] = line[count1];
			count2++;
		}
		count1++;
	}
	new_line[count2] = '\0';
	return (new_line);
}

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
