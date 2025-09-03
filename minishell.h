/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:50:28 by lpalomin          #+#    #+#             */
/*   Updated: 2025/08/23 09:29:06 by lpalomin         ###   ########.fr       */
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
# include <linux/limits.h>
# include "libft/libft.h"

extern volatile sig_atomic_t	g_signal;
extern int						g_exit_status;

typedef enum e_redir_type
{
	R_INFILE,
	R_OUTFILE,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
	int				fd_pipe[2];
}	t_redir;

typedef struct s_cmd
{
	int		amount_cmd;
	char	**argv;
	char	***pipe_argv;
	t_redir	**redirs;
}	t_cmd;

//signals.c
void	init_signals(void);
void	sigint_handler(int sig);
// cmd_utils.c
void	parse_line(t_cmd *cmd, char *line);
void	modify_status(char character, int *count);
void	add_to_cmd(t_cmd *cmd, char *new_line, int *count2);
void	print_cmd(char **argv);
// execute_utils.c
/* void	execute_cmd(t_cmd *cmd, char **envp);*/
char	*find_command_path(char *command, char **envp);
// quotes_utils.c
int		check_unclosed_quotes(char *line);
// dollar_utils.c
char	*expand_dollar_line(char *line, int position, char **envp);
char	*get_dollar_value(char *line, int start, char **envp);
int		search_dollars(char *line);
// more_dollar_utils.c
void	expand_dollars(t_cmd *cmd, char **envp);
char	*expand_all_dollars(char *line, char **envp);
// redirections.c
void	handle_redirections(t_redir *list);
void	handle_append(char *filename);
void	handle_infile(char *filename);
void	handle_outfile(char *filename);
// heredoc_utils.c
void	prepare_heredocs(t_cmd *cmd, char **envp);
// redir_utils.c
void	redirs_init(t_cmd *cmd);
void	add_redir(t_redir **list, t_redir_type type, char *s);
void	free_redirs_list(t_redir *list);
void	free_all_redirs(t_cmd *cmd);
// parse_redirs.c
void	die_child(char *msg);
void	parse_redirs_for_command(t_cmd *cmd, int count);
void	parse_all_redirs(t_cmd *cmd);
// handle_pipes.c
int		count_pipes(t_cmd *cmd);
void	parse_pipe_argv(t_cmd *cmd);
// execute_pipes.c
void	execute_pipes(t_cmd *cmd, char **envp);
// free_utils.c
void	error(void);
void	free_cmd(t_cmd *cmd);
void	free_split(char **split);
void	free_execve(t_cmd *cmd, char *cmd_path);
void	free_dollar_line(char *full_var, char *dollar_value,
			char *prefix, char *suffix);
// pipes_utils.c
int		is_parent_builtin(char *cmd_name);
int		setup_pipe(int pipe_fd[2], int is_last);
void	update_fds(int *prev_fd, int pipe_fd[2]);
// fork_utils.c
int		fork_and_exec(t_cmd *cmd, char **envp, int pipe_cmd, int *fds);
// execute_builtins.c
int		is_builtin(char *cmd_name);
int		execute_builtin(t_cmd *cmd, char **envp);
void	free_envp(char **envp);
// builtins.c
int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_export(t_cmd *cmd, char **envp);
int		builtin_unset(t_cmd *cmd, char **envp);
int		builtin_env(char **envp);
int		builtin_exit(t_cmd *cmd);
// other_utils.c
char	*remove_quotes(char *line);
char	*remove_char(char *line, char remove);
void	remove_argv_range(t_cmd *cmd, int pipe_cmd, int start, int count);
#endif
