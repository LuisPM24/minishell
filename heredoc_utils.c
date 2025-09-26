/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:21:08 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/28 17:21:21 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_loop(t_cmd *cmd, t_redir *redir, char **envp)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_all_dollars(cmd, line, envp);
		if (!expanded)
			expanded = ft_strdup("");
		free(line);
		ft_putstr_fd(expanded, redir->fd_pipe[1]);
		ft_putstr_fd("\n", redir->fd_pipe[1]);
		free(expanded);
	}
}

static void	handle_one_heredoc(t_cmd *cmd, t_redir *redir, char **envp)
{
	if (pipe(redir->fd_pipe) == -1)
	{
		perror("pipe heredoc");
		return ;
	}
	heredoc_loop(cmd, redir, envp);
	close(redir->fd_pipe[1]);
}

void	prepare_heredocs(t_cmd *cmd, char **envp)
{
	int		count;
	t_redir	*redir;

	count = 0;
	while (count < cmd->amount_cmd)
	{
		redir = cmd->redirs[count];
		while (redir)
		{
			if (redir->type == R_HEREDOC)
				handle_one_heredoc(cmd, redir, envp);
			redir = redir->next;
		}
		count++;
	}
}
