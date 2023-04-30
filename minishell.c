/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:42:45 by byejeon           #+#    #+#             */
/*   Updated: 2023/04/30 20:31:02 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>

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

int		**make_pipes(int num_of_pipe);
int		print_perror(char *str);
void	close_pipes_exept(int **pfd, int num_of_pipe, int *fd);
size_t	ft_strlen(const char *str);
char	*cmd_abs_path(char *cmd, char **paths);
char	*ft_strjoin(char const *s1, char const *s2);

int		exe_cmd_line(t_arg *arg, t_cmds *cmds, char **env);
void	setting(t_arg *arg, t_cmds *cmds);
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_arg	arg;
	t_cmds	cmds;
	setting(&arg, &cmds);
	exe_cmd_line(&arg, &cmds, env);
}
#include <string.h>
void	setting(t_arg *arg, t_cmds *cmds)
{
	arg->path = malloc(sizeof(char *) * 6);
	arg->path[0] = strdup("/usr/local/bin/");
	arg->path[1] = strdup("/usr/bin/");
	arg->path[2] = strdup("/bin/");
	arg->path[3] = strdup("/usr/sbin/");
	arg->path[4] = strdup("/sbin/");
	arg->path[5] = 0;
	arg->num_of_cmd = 1;

	cmds->cmd = malloc(sizeof(char *) * (3));
	cmds->cmd[0] = strdup("../push_swap/Random_sample/random");
	cmds->cmd[1] = strdup("500");
	//cmds->cmd[1] = 0;
	cmds->cmd[2] = 0;
	cmds->in_redir_type = malloc(sizeof(int));
	cmds->out_redir_type = malloc(sizeof(int));
	*cmds->in_redir_type = 1;
	*cmds->out_redir_type = 2;

	char	**infile = malloc(sizeof(char *) * 2);
	char	**outfile = malloc(sizeof(char *) * 2);
	infile[0] = strdup("infile");
	infile[1] = 0;
	outfile[0] = strdup("outfile");
	//outfile[0] = 0;
	outfile[1] = 0;
	cmds->infile = infile;
	cmds->outfile = outfile;
	cmds->next = 0;
	cmds->prev = 0;
}

typedef struct	s_execute_arg
{
	int		**pfd;
	int		fd[2];
	pid_t	*pid;
	int		i;
	char	*cmd_path;
}	t_execute_arg;

int		init(t_arg *arg, t_execute_arg *exe_arg);
void	pipe_redir(int **pfd, int i, int num_of_cmd);
void	in_redir(t_cmds *cmds, int *fd);
void	out_redir(t_cmds *cmds, int *fd);
int		is_relative_path(char *cmd);
void	i_hate_25_line(t_execute_arg *exe_arg, t_arg *arg, t_cmds *cmds);
int		exe_cmd_line(t_arg *arg, t_cmds *cmds, char **env)
{
	t_execute_arg	exe_arg;
	int				stat_loc;
	int				i;

	if (init(arg, &exe_arg))
		return (print_perror("error"));
	while (cmds)
	{
		exe_arg.pid[exe_arg.i] = fork();
		if (exe_arg.pid[exe_arg.i] == 0)
		{
			i_hate_25_line(&exe_arg, arg, cmds);
			execve(exe_arg.cmd_path, cmds->cmd, env);
			exit(print_perror(cmds->cmd[0]));
		}
		cmds = cmds->next;
		exe_arg.i++;
	}
	i = 0;
	while (i < arg->num_of_cmd)
		waitpid(exe_arg.pid[i++], &stat_loc, WUNTRACED);
	return (0);
}

void	i_hate_25_line(t_execute_arg *exe_arg, t_arg *arg, t_cmds *cmds)
{
	pipe_redir(exe_arg->pfd, exe_arg->i, arg->num_of_cmd);
	in_redir(cmds, exe_arg->fd);
	out_redir(cmds, exe_arg->fd);
	if (arg->num_of_cmd > 1)
		close_pipes_exept(exe_arg->pfd, arg->num_of_cmd, exe_arg->fd);
	if (is_relative_path(cmds->cmd[0]))
	{
		exe_arg->cmd_path = cmds->cmd[0];
		if (access(exe_arg->cmd_path, X_OK) == -1)
			exit(print_perror(exe_arg->cmd_path));
	}
	else
		exe_arg->cmd_path = cmd_abs_path(cmds->cmd[0], arg->path);
	if (exe_arg->cmd_path == 0)
		exit(print_perror(cmds->cmd[0]));
}

int	init(t_arg *arg, t_execute_arg *exe_arg)
{
	exe_arg->i = 0;
	exe_arg->fd[0] = -1;
	exe_arg->fd[1] = -1;
	exe_arg->pid = (pid_t *)malloc(sizeof(pid_t) * arg->num_of_cmd);
	if (exe_arg->pid == 0)
		return (1);
	if (arg->num_of_cmd)
	{
		exe_arg->pfd = make_pipes(arg->num_of_cmd - 1);
		if (exe_arg->pfd == 0)
		{
			free(exe_arg->pid);
			return (1);
		}
	}
	return (0);
}

int	is_relative_path(char *cmd)
{
	size_t	i;
	size_t	cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd);
	if (cmd_len >= 2 && cmd[0] == '.' && cmd[1] == '/')
	{
		return (1);
	}
	else if (cmd_len >= 3 && cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	out_redir(t_cmds *cmds, int *fd)
{
	int		i;
	char	**outfile;

	outfile = cmds->outfile;
	i = 0;
	while (outfile[i])
	{
		if (i != 0)
			close(fd[1]);
		if (access(outfile[i], F_OK) == 0)
			if (access(outfile[i], W_OK) != 0)
				exit(print_perror(outfile[i]));
		if (*cmds->out_redir_type == 1)
		{
			unlink(outfile[i]);
			fd[1] = open(outfile[i], O_WRONLY | O_CREAT, 0644);
		}
		else
			fd[1] = open(outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[1] < 0)
			exit(print_perror(outfile[i]));
		dup2(fd[1], 1);
		i++;
	}
}

void	in_redir(t_cmds *cmds, int *fd)
{
	int		i;
	char	**infile;

	infile = cmds->infile;
	i = 0;
	while (infile[i])
	{
		if (i != 0)
			close(fd[0]);
		if (access(infile[i], R_OK) == -1)
			exit(print_perror(infile[i]));
		fd[0] = open(infile[i], O_RDONLY);
		if (fd[0] < 0)
			exit(print_perror(infile[i]));
		dup2(fd[0], 0);
		i++;
	}
}

void	pipe_redir(int **pfd, int i, int num_of_cmd)
{
	if (i != 0)
		dup2(pfd[i - 1][0], 0);
	if (i != num_of_cmd - 1)
		dup2(pfd[i - 1][1], 1);
}

void	close_pipes_exept(int **pfd, int num_of_pipe, int *fd)
{
	int	i;

	i = 0;
	while (i < num_of_pipe)
	{
		if (pfd[i][0] != fd[0])
			close(pfd[i][0]);
		if (pfd[i][1] != fd[1])
			close(pfd[i][1]);
		i++;
	}
}

static int	**pipe_malloc_free(int **pfd, int i);
static int	**pipe_func_fail(int **pfd, int i);
int	**make_pipes(int num_of_pipe)
{
	int	i;
	int	**pfd;

	i = 0;
	pfd = malloc(sizeof(int *) * (num_of_pipe));
	if (pfd == 0)
		return (0);
	while (i < num_of_pipe)
	{
		pfd[i] = malloc(sizeof(int) * 2);
		if (pfd[i] == 0)
			return (pipe_malloc_free(pfd, i));
		if (pipe(pfd[i]) == -1)
			return (pipe_func_fail(pfd, i));
		i++;
	}
	return (pfd);
}

static int	**pipe_func_fail(int **pfd, int i)
{
	int	tmp;

	tmp = i;
	while (i--)
	{
		close(pfd[i][0]);
		close(pfd[i][1]);
	}
	return (pipe_malloc_free(pfd, tmp));
}

static int	**pipe_malloc_free(int **pfd, int i)
{
	while (i--)
		free(pfd[i]);
	free(pfd);
	return (0);
}

static char	*print_error_message(char *cmd, char *message);
static char	*print_perror_massage(char *cmd);
char	*cmd_abs_path(char *cmd, char **paths)
{
	char	*out;
	int		i;

	i = -1;
	while (paths[++i])
	{
		out = ft_strjoin(paths[i], cmd);
		if (out == 0)
			exit(print_perror(cmd));
		if (access(out, F_OK) == 0)
		{
			if (access(out, X_OK) == 0)
			{
				return (out);
			}
			else
			{
				free(out);
				return (print_perror_massage(cmd));
			}
		}
		else
			free(out);
	}
	return(print_error_message(cmd, ": command not found\n"));
}

static char	*print_perror_massage(char *cmd)
{
	perror(cmd);
	return (0);
}

static char *print_error_message(char *cmd, char *message)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, message, ft_strlen(message));
	return (0);
}

int	print_perror(char *str)
{
	perror(str);
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	out = malloc(sizeof(char) * (len + 1));
	if (out == 0)
		return (0);
	while (*s1)
		out[i++] = *(s1++);
	while (*s2)
		out[i++] = *(s2++);
	out[i] = '\0';
	return (out);
}
