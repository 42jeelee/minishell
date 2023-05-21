/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 00:04:34 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/21 21:10:58 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_PROMPT_H
# define NEW_PROMPT_H

# include "common.h"

typedef struct s_blockinfo
{
	int		word_size;
	int		start;
	int		end;
	char	quotes;
}	t_blockinfo;

t_cmds	*new_prompt(t_arg *arg);

int		parse_line(char *line, t_cmds **cmds, t_arg *arg);

t_cmds	*new_cmd(char **command, t_arg *arg);
void	add_cmd_list(t_cmds *new, t_cmds **list);
char	*ft_strchange(char *str, int start, int end, char *changestr);
char	*ft_tristrjoin(char *s1, char *s2, char *s3);
char	*rmbothend_str(char *word, int start, int end);

int		create_word_list(char ***list);
int		create_int_list(int **list);

int		init_shell(t_arg *arg, char **env);
int		init_cmd(t_cmds *cmd);

int		get_block_size(char *word, char c);
int		change_block_env(char **word, t_blockinfo *bi, t_arg *env);

int		rm_quotes_intoken(char **token, int i);
int		trim_word(char **word, t_arg *arg);

int		set_valueenv(char *key, char *value, char **env);
char	*get_value_env(char *key, int size, char **env);

char	**get_path(char **env);
char	**make_envlist(char **env);

void	free_words(char **words);
void	free_cmds(t_cmds *cmds);
void	free_arg(t_arg *arg);

int		quotes_blockidx(char *str);
int		is_in_idx(char *str, char *catchs);
int		str_in_idx(char *str, char *catchs);
int		get_env_size(char *word, int block_size);
int		is_builtin(char *word);
int		is_redirection(char *word);
char	*get_wordcatch(char *str, char *catchs);

void	change_term(struct termios *term);
void	no_echoctl(struct termios *old_term);

void	sig_handler(int signum);
void	sig_have_child(int signum);

void	sig_init(t_arg *arg);

#endif
