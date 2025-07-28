/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_dollar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:00:12 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/28 10:54:05 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_all_dollars(char *line, char **envp)
{
	int		pos;
	char	*new_line;
	char	*tmp;

	if (!line)
		return (NULL);
	tmp = ft_strdup(line);
	if (!tmp)
		return (NULL);
	pos = search_dollars(tmp);
	while (pos != -1)
	{
		new_line = expand_dollar_line(tmp, pos, envp);
		free(tmp);
		tmp = new_line;
		pos = search_dollars(tmp);
	}
	return (tmp);
}

void	expand_dollars(t_cmd *cmd, char **envp)
{
	int		count;
	char	*expanded;

	count = 0;
	while (cmd->argv && cmd->argv[count])
	{
		expanded = expand_all_dollars(cmd->argv[count], envp);
		free(cmd->argv[count]);
		cmd->argv[count] = expanded;
		count++;
	}
}
