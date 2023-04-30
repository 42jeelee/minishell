/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:38:43 by jeelee            #+#    #+#             */
/*   Updated: 2023/04/30 22:42:45 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "./libft/libft.h"

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

t_cmds	*new_prompt(int *num_of_cmd);

int		parse_line(char *line, t_cmds **cmds, int *num_of_cmd);

t_cmds	*new_cmd(char *commad);
void	add_cmd_list(t_cmds *new, t_cmds **list);

int		add_list_word(char *word, char ***list);
int		add_list_int(int num, int **list);
int		create_word_list(char ***list);
int		create_int_list(int **list);
int		init_cmd(t_cmds *cmd);
int		is_in_chars(char *str, char *inchars);

char	**get_path(char **env);
t_arg	*get_arg(int num_of_cmd, char **paths);

void	free_words(char **words);
void	free_cmds(t_cmds *cmds);
void	free_arg(t_arg *arg);

// PRINT
void	print_cmds(t_arg *arg, t_cmds *cmds);
void	print_arg(t_arg *arg);

#endif