/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:47:24 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/28 17:47:48 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_double_redir(t_cmd *cmd, char *line, char *new_line, int *i)
{
	new_line[0] = line[*i];
	new_line[1] = line[*i + 1];
	new_line[2] = '\0';
	cmd->argv[cmd->amount_cmd++] = ft_strdup(new_line);
	(*i)++;
}

static void	handle_single_redir(t_cmd *cmd, char *line, char *new_line, int i)
{
	new_line[0] = line[i];
	new_line[1] = '\0';
	cmd->argv[cmd->amount_cmd++] = ft_strdup(new_line);
}

static void	handle_operator(t_cmd *cmd, char *line, char *new_line, int *i)
{
	if ((line[*i] == '<' && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] == '>'))
		handle_double_redir(cmd, line, new_line, i);
	else
		handle_single_redir(cmd, line, new_line, *i);
}

static void	parse_loop(t_cmd *cmd, char *line,
			char *new_line, int *status)
{
	int	count1;
	int	count2;

	count1 = 0;
	count2 = 0;
	while (line[count1])
	{
		modify_status(line[count1], status);
		if ((line[count1] == ' ' || line[count1] == '|'
				|| line[count1] == '<' || line[count1] == '>')
			&& *status == 0)
		{
			add_to_cmd(cmd, new_line, &count2);
			if (line[count1] != ' ')
				handle_operator(cmd, line, new_line, &count1);
		}
		else
			new_line[count2++] = line[count1];
		count1++;
	}
	if (count2 > 0)
		add_to_cmd(cmd, new_line, &count2);
}

void	parse_line(t_cmd *cmd, char *line)
{
	int		status;
	char	*new_line;

	status = 0;
	new_line = malloc(ft_strlen(line) + 1);
	if (!new_line)
		return ;
	parse_loop(cmd, line, new_line, &status);
	free(new_line);
}
