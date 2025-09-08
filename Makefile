# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpalomin <lpalomin@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 08:37:02 by lpalomin          #+#    #+#              #
#    Updated: 2025/09/08 13:17:06 by lpalomin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell
SRCS =	minishell.c \
		signals.c \
		cmd_utils.c \
		parse_cmd.c \
		execute_utils.c \
		quotes_utils.c \
		dollar_utils.c \
		more_dollar_utils.c \
		redirections.c \
		heredoc_utils.c \
		redir_utils.c \
		handle_pipes.c \
		execute_pipes.c \
		fork_utils.c \
		free_utils.c \
		pipes_utils.c \
		execute_builtins.c \
		builtins.c \
		other_builtins.c \
		parse_utils.c \
		other_utils.c

OBJS =	$(SRCS:.c=.o)
CC =	cc
CFLAGS =	-Wall -Wextra -Werror
LDFLAGS = -lreadline
LIBFT =	libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft/

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft/ clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
