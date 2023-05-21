/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:16:24 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 15:30:06 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

# define INONE 2
# define INTWO 1
# define OUTONE 4
# define OUTTWO 3

typedef struct s_arg
{
	int		num_of_cmd;
	int		stat_loc;
	char	**env;
	void	(*old_sigint)(int);
	void	(*old_sigquit)(int);
}	t_arg;

typedef struct s_cmds
{
	int				builtin;
	char			**cmd;
	int				*redir_type;
	char			**file;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_execute_arg
{
	int		**pfd;
	int		fd[2];
	int		restore_fd[2];
	pid_t	*pid;
	int		i;
	char	**path;
	char	*cmd_path;
	char	**tmp_name;
}	t_execute_arg;

int		print_perror(char *str);

void	fork_sig_init(t_arg *arg);
void	parents_sig_init(void);
void	parents_sig_end(void);

char	**list_dup(char **list);
int		add_list_word(char *word, char ***list);
int		add_list_int(int num, int **list);
void	copy_list(char **new_list, char **old_list, int size);
int		ft_cmdssize(t_cmds *cmds);

#endif
