# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marco <marco@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 08:37:02 by lpalomin          #+#    #+#              #
#    Updated: 2025/08/19 14:50:11 by marco            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell
SRCS =	minishell.c \
		signals.c \
		cmd_utils.c \
		execute_utils.c \
		quotes_utils.c \
		dollar_utils.c \
		more_dollar_utils.c \
		redirections.c \
		free_utils.c \
		other_utils.c \
		execute_cd.c  \
		execute_echo.c \
		execute_pwd.c \
		execute_env.c \
		execute_builtin.c

OBJDIR = objs
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)
CC =	cc
CFLAGS =	-Wall -Wextra -Werror 
LIBFT =	libft/libft.a
RM := rm -fr

HEADERS := minishell.h

all: $(LIBFT) $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft/

clean:
	$(RM) $(OBJDIR)
	$(MAKE) -C libft/ clean

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
