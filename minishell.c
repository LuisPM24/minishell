/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:47:30 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/22 12:48:56 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void	minishell_procedure(t_cmd *cmd, char *line, char **envp)
{
	add_history(line);
	if (!check_unclosed_quotes(line))
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		return ;
	}
	parse_line(cmd, line);
	print_cmd(cmd);
	execute_cmd(cmd, envp);
	free_cmd(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	init_signals();
	while (1)
	{
		line = readline("\033[0;32mminishell$ \033[0m");
		if (!line)
			break ;
		else if (line)
			minishell_procedure(&cmd, line, envp);
	}
}
