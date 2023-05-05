/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:38:43 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/04 15:47:19 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./libft/libft.h"

# define INONE 2
# define INTWO 1
# define OUTONE 4
# define OUTTWO 3

typedef struct s_arg
{
	int		num_of_cmd;
	char	**path;
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
	pid_t	*pid;
	int		i;
	char	*cmd_path;
}	t_execute_arg;

// jeelee func
t_cmds	*new_prompt(int *num_of_cmd);

int		parse_line(char *line, t_cmds **cmds, int *num_of_cmd);

t_cmds	*new_cmd(char *commad);
void	add_cmd_list(t_cmds *new, t_cmds **list);

int		add_list_word(char *word, char ***list);
int		add_list_int(int num, int **list);
int		create_word_list(char ***list);
int		create_int_list(int **list);
int		init_cmd(t_cmds *cmd);

char	**get_path(char **env);
t_arg	*get_arg(int num_of_cmd, char **paths);

void	free_words(char **words);
void	free_cmds(t_cmds *cmds);
void	free_arg(t_arg *arg);

int		is_in_idx(char *str, char *catch);
char	*get_wordcatch(char *str, char *catch);
int		is_builtin(char *word);

// byejeon func
int		exe_cmd_line(t_arg *arg, t_cmds *cmds, char **env);
int		print_perror(char *str);
char	*cmd_abs_path(char *cmd, char **paths);
int		**make_pipes(int num_of_pipe);
void	close_pipes_exept(int **pfd, int num_of_pipe, int *fd);
int		is_relative_path(char *cmd);

void	pipe_redir(int **pfd, int i, int num_of_cmd, int *fd);
void	redir(char **file, int *redir_type, int *fd);

// PRINT
void	print_cmds(t_arg *arg, t_cmds *cmds);
void	print_arg(t_arg *arg);

#endif
