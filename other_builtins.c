/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:12:57 by lpalomin          #+#    #+#             */
/*   Updated: 2025/09/01 14:13:11 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_env_var(char **env, char *str)
{
	int		count;
	size_t	len;
	char	*name;

	if (!env || !str)
		return ;
	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	name = strndup(str, len);
	if (!name)
		return ;
	count = 0;
	while (env[count])
	{
		if (ft_strncmp(env[count], name, len) == 0 && env[count][len] == '=')
			return (free(env[count]), env[count] = ft_strdup(str), free(name));
		count++;
	}
	env[count] = strdup(str);
	env[count + 1] = NULL;
	free(name);
}

int	builtin_export(t_cmd *cmd, char **envp)
{
	int	count;

	if (!envp)
		return (1);
	count = 1;
	while (cmd->argv[count])
	{
		put_env_var(envp, cmd->argv[count]);
		count++;
	}
	return (0);
}

static void	unset_env_var(char **envp, char *name)
{
	int		count;
	size_t	len;

	if (!envp || !name)
		return ;
	len = strlen(name);
	count = 0;
	while (envp[count])
	{
		if (strncmp(envp[count], name, len) == 0 && envp[count][len] == '=')
		{
			free(envp[count]);
			while (envp[count + 1])
			{
				envp[count] = envp[count + 1];
				count++;
			}
			envp[count] = NULL;
			return ;
		}
		count++;
	}
}

int	builtin_unset(t_cmd *cmd, char **envp)
{
	int	count;

	if (!envp)
		return (1);
	count = 1;
	while (cmd->argv[count])
	{
		unset_env_var(envp, cmd->argv[count]);
		count++;
	}
	return (0);
}
