/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:21:57 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/29 13:58:18 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_dollars(char *line)
{
	int	position;
	int	status;

	position = 0;
	status = 0;
	if (!line || !*line)
		return (-1);
	while (line[position])
	{
		modify_status(line[position], &status);
		if (line[position] == '$' && (status == 2 || status == 0))
		{
			if (line[position + 1] == '\0')
				return (-1);
			return (position);
		}
		position++;
	}
	return (-1);
}

static char	*get_variable_name(char *line, int start)
{
	int	end;

	end = start + 1;
	if (line[start] && line[start] != '$')
		return (NULL);
	if (line[end] == '?')
		return (ft_strdup("?"));
	if (!line[end] || !(ft_isalnum(line[end]) || line[end] == '_'))
		return (ft_strdup("$"));
	if (line[end] == '{')
	{
		end++;
		while (line[end] && ft_isalnum(line[end]))
			end++;
		if (line[end] != '}')
			return (NULL);
		return (ft_substr(line, start + 2, end - (start + 2)));
	}
	while (line[end] && ft_isalnum(line[end]))
		end++;
	return (ft_substr(line, start + 1, end - (start + 1)));
}

static char	*get_env_value(char *var_name, char **envp)
{
	char	*equal_sign;
	int		count;

	count = 0;
	while (envp[count])
	{
		if (ft_strncmp(envp[count], var_name, ft_strlen(var_name)) == 0
			&& envp[count][ft_strlen(var_name)] == '=')
			break ;
		count++;
	}
	if (!envp[count])
		return (ft_strdup(""));
	equal_sign = ft_strchr(envp[count], '=');
	if (!equal_sign)
		return (NULL);
	return (ft_strdup(equal_sign + 1));
}

char	*get_dollar_value(t_cmd *cmd, char *line, int start, char **envp)
{
	char	*var_name;
	char	*value;

	var_name = get_variable_name(line, start);
	if (!var_name)
		return (ft_strdup(""));
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (free(var_name), ft_itoa(cmd->exit_status));
	if (ft_strncmp(var_name, "$", 2) == 0)
		return (free(var_name), ft_strdup("$"));
	value = get_env_value(var_name, envp);
	free(var_name);
	return (value);
}

// Que alguien me mate.c
char	*expand_dollar_line(t_cmd *cmd, char *line, int position, char **envp)
{
	char	*full_var;
	char	*dollar_value;
	char	*prefix;
	char	*suffix;
	char	*new_line;

	full_var = extract_full_var(line, position);
	if (!full_var)
		return (ft_putstr_fd("Error: bad substitution", 2), NULL);
	dollar_value = get_dollar_value(cmd, line, position, envp);
	if (!dollar_value)
		dollar_value = ft_strdup("");
	prefix = ft_substr(line, 0, position);
	suffix = ft_strdup(line + position + ft_strlen(full_var));
	new_line = ft_strjoin(prefix, dollar_value);
	free(prefix);
	prefix = new_line;
	new_line = ft_strjoin(prefix, suffix);
	free_dollar_line(full_var, dollar_value, prefix, suffix);
	return (new_line);
}
