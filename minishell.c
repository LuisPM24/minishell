/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmembril <mmembril@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:47:30 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/26 17:25:27 by mmembril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// My little envp 🌈🦄
static char	**dup_envp(char **envp)
{
	int		env_count;
	int		count;
	char	**new_env;

	if (!envp)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	new_env = malloc((count + 100) * sizeof(char *));
	if (!new_env)
		return (NULL);
	env_count = 0;
	while (env_count < count)
	{
		new_env[env_count] = ft_strdup(envp[env_count]);
		if (!new_env[env_count])
			return (free_split(new_env), NULL);
		env_count++;
	}
	new_env[env_count] = NULL;
	return (new_env);
}

static int	init_cmd(t_cmd *cmd)
{
	cmd->amount_cmd = 0;
	cmd->argv = malloc(sizeof(char *) * 30);
	if (!cmd->argv)
		return (1);
	cmd->argv[0] = NULL;
	cmd->pipe_argv = NULL;
	cmd->redirs = NULL;
	return (0);
}

static void	minishell_procedure(t_cmd *cmd, char *line, char **envp)
{
	if (init_cmd(cmd))
		return (free_cmd(cmd));
	if (!check_unclosed_quotes(line))
	{
		free_cmd(cmd);
		return (ft_putstr_fd("Error: unclosed quote\n", 2));
	}
	parse_line(cmd, line);
	cmd->argv[cmd->amount_cmd] = NULL;
	expand_dollars(cmd, envp);
	if (cmd->amount_cmd == 0 || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (free_cmd(cmd));
	parse_pipe_argv(cmd);
	cmd->amount_cmd = count_pipes(cmd) + 1;
	while (cmd->pipe_argv[cmd->amount_cmd])
		cmd->amount_cmd++;
	redirs_init(cmd);
	parse_all_redirs(cmd);
	prepare_heredocs(cmd, envp);
	remove_quotes_pipe_argv(cmd);
	execute_pipes(cmd, envp);
	free_cmd(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**my_little_envp;
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	my_little_envp = dup_envp(envp);
	init_signals();
	cmd.exit_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		minishell_procedure(&cmd, line, my_little_envp);
		free(line);
	}
	free_envp(my_little_envp);
	rl_clear_history();
	return (0);
}
