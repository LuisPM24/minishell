/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:42:32 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/04 09:14:03 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_cmd *cmd, int index)
{
	int		fd[2];
	char	*line;
	char	*delimiter;

	if (!cmd->argv[index + 1])
		return (ft_putstr_fd("Error: No heredoc redirection", 2));
	delimiter = cmd->argv[index + 1];
	if (pipe(fd) == -1)
		return (perror("pipe"));
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	remove_argv_range(cmd, index, 2);
}

void	handle_append(t_cmd *cmd, int index)
{
	int		fd;
	char	*filename;

	filename = cmd->argv[index + 1];
	if (!filename)
		return (ft_putstr_fd("Error: Invalid name after append", 2));
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
	remove_argv_range(cmd, index, 2);
}

void	handle_infile(t_cmd *cmd, int index)
{
	int		fd;
	char	*filename;

	filename = cmd->argv[index + 1];
	if (!filename)
		return (ft_putstr_fd("Error: Missing infile redirection", 2));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("open"));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
	remove_argv_range(cmd, index, 2);
}

void	handle_outfile(t_cmd *cmd, int index)
{
	int		fd;
	char	*filename;

	filename = cmd->argv[index + 1];
	if (!filename)
		return (ft_putstr_fd("Error: Missing name after outfile", 2));
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 (outfile)");
		close(fd);
		return ;
	}
	close(fd);
	remove_argv_range(cmd, index, 2);
}

void	handle_redirections(t_cmd *cmd)
{
	int	count;

	count = 0;
	if (!cmd || !cmd->argv[0])
		return ;
	while (cmd->argv[count])
	{
		if (ft_strcmp(cmd->argv[count], "<<") == 0
			|| ft_strcmp(cmd->argv[count], ">>") == 0
			|| ft_strcmp(cmd->argv[count], "<") == 0
			|| ft_strcmp(cmd->argv[count], ">") == 0)
		{
			throw_redirection(cmd, count);
			continue ;
		}
		count++;
	}
}
