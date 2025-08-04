/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:23:48 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/29 13:59:04 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(void)
{
	perror("Error");
}

void	free_cmd(t_cmd *cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return ;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			free(cmd->argv[count++]);
		free(cmd->argv);
	}
}

void	free_split(char **split)
{
	int	count;

	count = 0;
	while (split[count])
	{
		free(split[count]);
		count++;
	}
	free(split);
}

void	free_execve(t_cmd *cmd, char *cmd_path)
{
	free_cmd(cmd);
	free(cmd_path);
	perror("minishell");
	exit(EXIT_FAILURE);
}

void	free_dollar_line(char *full_var, char *dollar_value,
			char *prefix, char *suffix)
{
	if (full_var)
		free(full_var);
	if (dollar_value)
		free(dollar_value);
	if (prefix)
		free(prefix);
	if (suffix)
		free(suffix);
}
