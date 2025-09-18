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
	env[count] = ft_strdup(str);
	env[count + 1] = NULL;
	free(name);
}

static int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!((str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= 'a' && str[0] <= 'z')
			|| str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_export(t_cmd *cmd, int pipe_cmd, char **envp)
{
	int	count;
	int	status;

	if (!envp)
		return (1);
	count = 1;
	status = 0;
	while (cmd->pipe_argv[pipe_cmd][count])
	{
		if (!is_valid_identifier(cmd->argv[count]))
		{
			put_error(cmd->argv[count]);
			status = 1;
		}
		else
			put_env_var(envp, cmd->argv[count]);
		count++;
	}
	return (status);
}

static void	unset_env_var(char **envp, char *name)
{
	int		count;
	size_t	len;

	if (!envp || !name)
		return ;
	len = ft_strlen(name);
	count = 0;
	while (envp[count])
	{
		if (ft_strncmp(envp[count], name, len) == 0 && envp[count][len] == '=')
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

int	builtin_unset(t_cmd *cmd, int pipe_cmd, char **envp)
{
	int	count;

	if (!envp)
		return (1);
	count = 1;
	while (cmd->pipe_argv[pipe_cmd][count])
	{
		unset_env_var(envp, cmd->pipe_argv[pipe_cmd][count]);
		count++;
	}
	return (0);
}
