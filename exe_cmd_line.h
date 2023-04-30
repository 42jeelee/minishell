/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:57 by byejeon           #+#    #+#             */
/*   Updated: 2023/04/30 21:49:23 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_CMD_LINE_H
# define EXE_CMD_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_arg
{
	int		num_of_cmd;
	char	**path;
}	t_arg;

typedef struct s_cmds
{
	char			**cmd;
	int				*in_redir_type;
	int				*out_redir_type;
	char			**infile;
	char			**outfile;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct	s_execute_arg
{
	int		**pfd;
	int		fd[2];
	pid_t	*pid;
	int		i;
	char	*cmd_path;
}	t_execute_arg;


int		exe_cmd_line(t_arg *arg, t_cmds *cmds, char **env);
int		print_perror(char *str);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*cmd_abs_path(char *cmd, char **paths);
int		**make_pipes(int num_of_pipe);
void	close_pipes_exept(int **pfd, int num_of_pipe, int *fd);
int		is_relative_path(char *cmd);

void	pipe_redir(int **pfd, int i, int num_of_cmd);
void	in_redir(t_cmds *cmds, int *fd);
void	out_redir(t_cmds *cmds, int *fd);

#endif
