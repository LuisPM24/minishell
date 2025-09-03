/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:20:37 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/26 09:21:00 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirs_init(t_cmd *cmd)
{
	if (cmd->amount_cmd == 0)
		return ;
	cmd->redirs = calloc(cmd->amount_cmd, sizeof(t_redir *));
}

void	add_redir(t_redir **list, t_redir_type type, char *target)
{
	t_redir	*aux_red;
	t_redir	*cur;

	aux_red = malloc(sizeof(*aux_red));
	cur = NULL;
	if (!aux_red)
		return ;
	aux_red->type = type;
	aux_red->target = ft_strdup(target);
	aux_red->next = NULL;
	if (!*list)
	{
		*list = aux_red;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = aux_red;
}

void	free_redirs_list(t_redir *list)
{
	t_redir	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->target);
		free(list);
		list = tmp;
	}
}

void	free_all_redirs(t_cmd *cmd)
{
	int	count;

	if (!cmd || !cmd->redirs)
		return ;
	count = 0;
	while (count < cmd->amount_cmd)
	{
		if (cmd->redirs[count])
			free_redirs_list(cmd->redirs[count]);
		count++;
	}
	free(cmd->redirs);
	cmd->redirs = NULL;
}
