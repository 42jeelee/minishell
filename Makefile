NAME = exe_cmd_line_test

SRC = close_pipes_exept.c cmd_abs_path.c exe_cmd_line.c ft_strjoin.c ft_strlen.c is_relative_path.c make_pipes.c print_perror.c redir.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = -lreadline

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re :
	make clean
	make all

.PHONY: all clean fclean re
