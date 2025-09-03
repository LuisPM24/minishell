/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:42:32 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/23 09:32:54 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		die_child("open >>");
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		die_child("dup2 >>");
	}
	close(fd);
}

void	handle_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		die_child("open <");
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		die_child("dup2 <");
	}
	close(fd);
}

void	handle_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		die_child("open >");
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		die_child("dup2 >");
	}
	close(fd);
}

void	handle_redirections(t_redir *list)
{
	t_redir	*redir;

	redir = list;
	while (redir)
	{
		if (redir->type == R_INFILE)
			handle_infile(redir->target);
		else if (redir->type == R_OUTFILE)
			handle_outfile(redir->target);
		else if (redir->type == R_APPEND)
			handle_append(redir->target);
		else if (redir->type == R_HEREDOC)
		{
			if (dup2(redir->fd_pipe[0], STDIN_FILENO) == -1)
			{
				perror("dup2 heredoc");
				exit(1);
			}
			close(redir->fd_pipe[0]);
		}
		redir = redir->next;
	}
}
