/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:21:57 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/28 13:49:08 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_dollars(char *line)
{
	int	position;
	int	status;

	position = 0;
	status = 0;
	if (!line)
		return (-1);
	while (line[position])
	{
		modify_status(line[position], &status);
		if (line[position] == '$' && (status == 2 || status == 0))
			return (position);
		position++;
	}
	return (-1);
}

static char	*get_variable_name(char *line, int start)
{
	int	end;

	if (line[start] && line[start] != '$')
		return (NULL);
	start++;
	if (line[start] == '{')
		start++;
	end = start;
	while (line[end] && ft_isalnum(line[end])) //Ahora ft_isalnum acepta tmbn barra bajas (_)
		end++;
	return (ft_substr(line, start, end - start));
}

char	*get_dollar_value(char *line, int start, char **envp)
{
	char	*var_name;
	char	*equal_sign;
	int		count;

	var_name = get_variable_name(line, start);
	if (!var_name)
		return (ft_strdup(""));
	count = 0;
	while (envp[count])
	{
		if (ft_strncmp(envp[count], var_name, ft_strlen(var_name)) == 0
			&& envp[count][ft_strlen(var_name)] == '=')
			break ;
		count++;
	}
	if (!envp[count])
		return (free(var_name), ft_strdup(""));
	equal_sign = ft_strchr(envp[count], '=');
	if (!envp[count] || !equal_sign)
		return (NULL);
	free(var_name);
	return (ft_strdup(equal_sign + 1));
}

static char	*extract_full_var(char *line, int position)
{
	int	start;
	int	count;

	if (!line || line[position] != '$')
		return (NULL);
	count = position + 1;
	if (line[count] == '{')
	{
		count++;
		start = count;
		while (line[count] && ft_isalnum(line[count]))
			count++;
		if (count == start || line[count] != '}')
			return (NULL);
		count++;
	}
	else
	{
		if (!ft_isalnum(line[count]))
			return (NULL);
		while (line[count] && ft_isalnum(line[count]))
			count++;
	}
	return (ft_substr(line, position, count - position));
}

// Que alguien me mate.c
char	*expand_dollar_line(char *line, int position, char **envp)
{
	char	*full_var;
	char	*dollar_value;
	char	*prefix;
	char	*suffix;
	char	*new_line;

	full_var = extract_full_var(line, position);
	if (!full_var)
		return (ft_putstr_fd("Error: bad substitution", 2), NULL);
	dollar_value = get_dollar_value(line, position, envp);
	if (!dollar_value)
		dollar_value = ft_strdup("");
	prefix = ft_substr(line, 0, position);
	suffix = ft_strdup(line + position + ft_strlen(full_var));
	new_line = ft_strjoin(prefix, dollar_value);
	free(prefix);
	prefix = new_line;
	new_line = ft_strjoin(prefix, suffix);
	free(full_var);
	free(dollar_value);
	free(prefix);
	free(suffix);
	return (new_line);
}
