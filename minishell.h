/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:50:28 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/28 09:17:36 by lpalomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

extern volatile sig_atomic_t	g_signal;

typedef struct s_cmd
{
	int		amount_cmd;
	char	**argv;
}	t_cmd;

//signals.c
void	init_signals(void);
void	sigint_handler(int sig);
// cmd_utils.c
void	parse_line(t_cmd *cmd, char *line);
void	modify_status(char character, int *count);
void	print_cmd(t_cmd *cmd);
// execute_utils.c
void	execute_cmd(t_cmd *cmd, char **envp);
// quotes_utils.c
int		check_unclosed_quotes(char *line);
// dollar_utils.c
char	*expand_dollar_line(char *line, int position, char **envp);
char	*get_dollar_value(char *line, int start, char **envp);
int		search_dollars(char *line);
// more_dollar_utils.c
void	expand_dollars(t_cmd *cmd, char **envp);
// free_utils.c
void	error(void);
void	free_cmd(t_cmd *cmd);
void	free_split(char **split);
void	free_execve(t_cmd *cmd, char *cmd_path);
// other_utils.c
char	*remove_char(char *line, char remove);
#endif
