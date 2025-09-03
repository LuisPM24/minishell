/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:21:02 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/19 09:26:10 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*form_path(char **paths, char *command)
{
	char	*command_path;
	char	*command_fullpath;
	int		count;

	count = 0;
	while (paths[count])
	{
		command_path = ft_strjoin(paths[count], "/");
		command_fullpath = ft_strjoin(command_path, command);
		free(command_path);
		if (access(command_fullpath, X_OK) == 0)
		{
			free_split(paths);
			return (command_fullpath);
		}
		free(command_fullpath);
		count++;
	}
	free_split(paths);
	return (NULL);
}

char	*find_command_path(char *command, char **envp)
{
	char	**paths;
	int		count;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	count = 0;
	while (envp[count] && ft_strnstr(envp[count], "PATH", 4) == 0)
		count++;
	if (!envp[count])
		return (NULL);
	paths = ft_split(envp[count] + 5, ':');
	if (!paths)
		return (NULL);
	return (form_path(paths, command));
}
