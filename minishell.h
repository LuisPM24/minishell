/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:50:28 by lpalomin          #+#    #+#             */
/*   Updated: 2025/07/22 12:49:34 by lpalomin         ###   ########.fr       */
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
void	print_cmd(t_cmd *cmd);
// execute_utils.c
void	execute_cmd(t_cmd *cmd, char **envp);
// quotes_utils.c
int		check_unclosed_quotes(char *line);
// free_utils.c
void	error(void);
void	free_cmd(t_cmd *cmd);
void	free_split(char **split);
void	free_execve(t_cmd *cmd, char *cmd_path);
// other_utils.c
char	*remove_char(char *line, char remove);
#endif
