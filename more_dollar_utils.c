/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_dollar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:00:12 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/29 10:10:22 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_all_dollars(char *line, char **envp)
{
	char	*tmp;
	char	*new_line;
	int		pos;
	int		offset;

	if (!line)
		return (NULL);
	tmp = ft_strdup(line);
	if (!tmp)
		return (NULL);
	offset = 0;
	pos = search_dollars(tmp + offset);
	while (pos != -1)
	{
		pos += offset;
		new_line = expand_dollar_line(tmp, pos, envp);
		free(tmp);
		tmp = new_line;
		if (!tmp)
			return (NULL);
		offset = pos + 1;
		if (offset >= (int)ft_strlen(tmp))
			offset = 0;
		pos = search_dollars(tmp + offset);
	}
	return (tmp);
}

void	remove_quotes_pipe_argv(t_cmd *cmd)
{
	int		count1;
	int		count2;
	char	*rm_quotes;

	count1 = 0;
	while (count1 < cmd->amount_cmd)
	{
		count2 = 0;
		while (cmd->pipe_argv[count1] && cmd->pipe_argv[count1][count2])
		{
			rm_quotes = remove_last_quotes(cmd->pipe_argv[count1][count2]);
			if (rm_quotes && rm_quotes != cmd->pipe_argv[count1][count2])
			{
				free(cmd->pipe_argv[count1][count2]);
				cmd->pipe_argv[count1][count2] = rm_quotes;
			}
			count2++;
		}
		count1++;
	}
}

void	expand_dollars(t_cmd *cmd, char **envp)
{
	int		count;
	int		i;
	char	*expanded;
	char	*rm_quotes;

	count = 0;
	while (cmd->argv && cmd->argv[count])
	{
		expanded = expand_all_dollars(cmd->argv[count], envp);
		if (!expanded || expanded[0] == '\0')
		{
			free(cmd->argv[count]);
			free(expanded);
			i = count;
			while (cmd->argv[i])
			{
			cmd->argv[i] = cmd->argv[i + 1];
				i++;
			}
			continue ;
		}
		free(cmd->argv[count]);
		rm_quotes = remove_quotes(expanded);
		if (rm_quotes && rm_quotes != expanded)
		{
			free(expanded);
			cmd->argv[count] = rm_quotes;
		}
		else
			cmd->argv[count] = expanded;
		count++;
	}
}
