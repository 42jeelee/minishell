# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 20:55:40 by jeelee            #+#    #+#              #
#    Updated: 2023/05/08 00:18:03 by jeelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	CC
CFLAGS		=	-Wall -Wextra -Werror

LIBDIR		=	./libft
LIBFT		=	$(LIBDIR)/libft.a

RLDIR		=	/usr/local/opt/readline/lib

SRC			=	main.c get_path.c new_prompt.c parse_line.c command.c \
				utils.c utils2.c utils3.c utils4.c free_it.c print_it.c init.c \
				term_env.c \
				close_pipes_exept.c cmd_abs_path.c exe_cmd_line.c \
				is_relative_path.c make_pipes.c print_perror.c redir.c \
				run_builtin.c

OBJ			=	$(SRC:.c=.o)

$(NAME)		:	$(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -L$(LIBDIR) -lft -L$(RLDIR) -lreadline $(OBJ) -o $@

%.o			:	%.c
	$(CC) $(CFLAGS) -c $?

$(LIBFT)	:
	make -C $(LIBDIR)

all			:	$(NAME)

clean		:
	@rm -f $(OBJ)

fclean		:	clean
	@rm -f $(NAME)

re			:
	@make fclean
	@make all

.PHONY		:	all clean fclean re
