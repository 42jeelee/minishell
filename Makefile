# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 20:55:40 by jeelee            #+#    #+#              #
#    Updated: 2023/04/30 21:02:12 by jeelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	CC
CFLAGS		=	-Wall -Wextra -Werror

LIBDIR		=	./libft
LIBFT		=	$(LIBDIR)/libft.a

SRC			=	main.c get_args.c new_prompt.c parse_line.c command.c \
				utils.c free_it.c print_it.c

OBJ			=	$(SRC:.c=.o)

$(NAME)		:	$(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -L$(LIBDIR) -lft -lreadline $(OBJ) -o $@

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