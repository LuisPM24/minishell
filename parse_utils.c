/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:32:43 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/26 09:32:58 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	die_child(char *msg)
{
	perror(msg);
	exit(1);
}

static int	is_redir_token(const char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"));
}

static t_redir_type	get_redir_type(const char *s)
{
	if (ft_strcmp(s, "<") == 0)
		return (R_INFILE);
	if (ft_strcmp(s, ">") == 0)
		return (R_OUTFILE);
	if (ft_strcmp(s, ">>") == 0)
		return (R_APPEND);
	return (R_HEREDOC);
}

void	parse_redirs_for_command(t_cmd *cmd, int i)
{
	char			**av;
	int				j;
	t_redir_type	type;

	av = cmd->pipe_argv[i];
	j = 0;
	while (av[j])
	{
		if (is_redir_token(av[j]))
		{
			if (!av[j + 1])
			{
				ft_putstr_fd(
					"minishell: syntax error near redirection\n", 2);
				break ;
			}
			type = get_redir_type(av[j]);
			add_redir(&cmd->redirs[i], type, av[j + 1]);
			remove_argv_range(cmd, i, j, 2);
		}
		else
			j++;
	}
}

void	parse_all_redirs(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (count < cmd->amount_cmd)
	{
		parse_redirs_for_command(cmd, count);
		count++;
	}
}
