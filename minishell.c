/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:47:30 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/24 17:33:32 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmd(t_cmd *cmd)
{
	cmd->amount_cmd = 0;
	cmd->argv = malloc(sizeof(char *) * 30); // 29 argumentos mas 1 NULL
	if (!cmd->argv)
		return (1);
	cmd->argv[0] = NULL;
	return (0);
}

static void	minishell_procedure(t_cmd *cmd, char *line, char ***envp)
{
	add_history(line);
	if (init_cmd(cmd))
		return ;
	if (!check_unclosed_quotes(line))
		return (ft_putstr_fd("Error: unclosed quote\n", 2));
	parse_line(cmd, line);
	cmd->argv[cmd->amount_cmd] = NULL;
	expand_dollars(cmd, *envp);
	print_cmd(cmd);
	if (cmd->amount_cmd == 0 || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (free_cmd(cmd));
	execute_cmd(cmd, envp);
	free_cmd(cmd);
}

static char **ft_cpy_envp(char **envp)
{
	char **cpy_envp;
	int i;

	i = 0;
	while (envp[i])
		i++;
	cpy_envp = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (envp[i])
	{
		cpy_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (cpy_envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**cpy_envp;
	t_cmd	cmd;
	

	(void)argc;
	(void)argv;
	init_signals();
	cpy_envp = ft_cpy_envp(envp);
	while (1)
	{
		line = readline("\033[0;32mminishell$ \033[0m");
		if (!line)
			break ;
		else if (line)
		{
			minishell_procedure(&cmd, line, &cpy_envp);
			free(line);
		}
	}
}
