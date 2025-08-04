/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:50:28 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/04 09:08:08 by lpalomin         ###   ########.fr       */
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
# include <fcntl.h>
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
// redirections.c
void	handle_redirections(t_cmd *cmd);
void	handle_heredoc(t_cmd *cmd, int index);
void	handle_append(t_cmd *cmd, int index);
void	handle_infile(t_cmd *cmd, int index);
void	handle_outfile(t_cmd *cmd, int index);
// free_utils.c
void	error(void);
void	free_cmd(t_cmd *cmd);
void	free_split(char **split);
void	free_execve(t_cmd *cmd, char *cmd_path);
void	free_dollar_line(char *full_var, char *dollar_value,
			char *prefix, char *suffix);
// other_utils.c
char	*remove_quotes(char *line);
char	*remove_char(char *line, char remove);
void	remove_argv_range(t_cmd *cmd, int start, int count);
void	throw_redirection(t_cmd *cmd, int count);
#endif
