/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:19:48 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/04 09:05:52 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_argv_range(t_cmd *cmd, int start, int count)
{
	int	count2;

	count2 = start;
	while (cmd->argv[count + count2])
	{
		cmd->argv[count2] = cmd->argv[count + count2];
		count2++;
	}
	while (cmd->argv[count2])
		cmd->argv[count2++] = NULL;
	cmd->amount_cmd -= count;
}

char	*remove_quotes(char *line)
{
	int		len;
	char	*result;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len < 2)
		return (NULL);
	if ((line[0] == '\'' && line[len - 1] == '\'')
		|| (line[0] == '"' && line[len - 1] == '"'))
	{
		result = ft_substr(line, 1, len - 2);
		free(line);
		return (result);
	}
	return (NULL);
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

void	throw_redirection(t_cmd *cmd, int count)
{
	if (ft_strcmp(cmd->argv[count], "<<") == 0)
		handle_heredoc(cmd, count);
	else if (ft_strcmp(cmd->argv[count], ">>") == 0)
		handle_append(cmd, count);
	else if (ft_strcmp(cmd->argv[count], "<") == 0)
		handle_infile(cmd, count);
	else if (ft_strcmp(cmd->argv[count], ">") == 0)
		handle_outfile(cmd, count);
}
