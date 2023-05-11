# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 20:55:40 by jeelee            #+#    #+#              #
#    Updated: 2023/05/11 18:30:49 by jeelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	CC
CFLAGS		=	-Wall -Wextra -Werror

LIBDIR		=	./libft
LIBFT		=	$(LIBDIR)/libft.a

RLDIR		=	/opt/homebrew/opt/readline/lib
RLINC		=	/opt/homebrew/opt/readline/include

SRC			=	main.c get_path.c new_prompt.c parse_line.c command.c \
				utils.c utils2.c utils3.c utils4.c free_it.c print_it.c init.c \
				term_env.c sig_control.c change_cmdenv.c trim_cmds.c \
				close_pipes_exept.c cmd_abs_path.c exe_cmd_line.c \
				is_relative_path.c make_pipes.c print_perror.c redir.c \
				run_builtin.c exe_cd.c exe_export.c

OBJ			=	$(SRC:.c=.o)

$(NAME)		:	$(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -L$(RLDIR) -lreadline $(LIBFT) $(OBJ) -o $@

%.o			:	%.c
	$(CC) $(CFLAGS) -I$(RLINC) -c $?

$(LIBFT)	:
	make -C $(LIBDIR)

all			:	$(NAME)

clean		:
	@make -C $(LIBDIR) clean
	@rm -f $(OBJ)

fclean		:	clean
	@rm -f $(NAME) $(LIBFT)

re			:
	@make fclean
	@make all

.PHONY		:	all clean fclean re
