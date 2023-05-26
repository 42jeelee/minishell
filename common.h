/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:16:24 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/26 16:18:13 by jeelee           ###   ########.fr       */
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
	char	*pwd;
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
	int				**pfd;
	int				fd[2];
	int				restore_fd[2];
	pid_t			*pid;
	int				i;
	int				child_num;
	char			**path;
	char			*cmd_path;
	char			**tmp_name;
	int				exit_code;
	struct s_arg	*arg;
}	t_execute_arg;

typedef struct s_blockinfo
{
	int		word_size;
	int		start;
	int		end;
	char	quotes;
	int		quotes_start;
}	t_blockinfo;

int		print_perror(char *str);

void	fork_sig_init(int sigquit);
void	parents_sig_init(void);
void	parents_sig_end(void);

void	change_term(struct termios *term);
void	no_echoctl(struct termios *old_term);

int		set_g_pwd(t_arg *arg);

char	**list_dup(char **list);
void	bi_init(char *word, t_blockinfo *bi);
int		change_env_block(char **word, t_blockinfo *bi, t_arg *arg);
int		change_quotes_block(char **word, t_blockinfo *bi, t_arg *arg);
int		change_trim_block(char **word, t_arg *arg, \
					int (*f)(char**, t_blockinfo*, t_arg*));
int		add_list_word(char *word, char ***list);
int		add_list_int(int num, int **list);
int		get_list_size(char **list);
void	copy_list(char **new_list, char **old_list, int size);
int		ft_cmdssize(t_cmds *cmds);

#endif
