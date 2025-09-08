# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marco <marco@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 08:37:02 by lpalomin          #+#    #+#              #
#    Updated: 2025/09/08 16:49:44 by marco            ###   ########.fr        #
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

OBJDIR = objs
OBJS =	$(SRCS:%.c=$(OBJDIR)/%.o)
CC =	cc
CFLAGS =	-Wall -Wextra -Werror
LDFLAGS = -lreadline
LIBFT =	libft/libft.a

all: $(LIBFT) $(NAME)

$(OBJDIR)/%.o: %.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft/

clean:
	rm -fr $(OBJDIR)
	$(MAKE) -C libft/ clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
