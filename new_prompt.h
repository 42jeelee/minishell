/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 00:04:34 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/08 02:56:29 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_PROMPT_H
# define NEW_PROMPT_H

# include "common.h"

t_cmds	*new_prompt(int *num_of_cmd);

int		parse_line(char *line, t_cmds **cmds, int *num_of_cmd);

t_cmds	*new_cmd(char *commad);
void	add_cmd_list(t_cmds *new, t_cmds **list);

int		create_word_list(char ***list);
int		create_int_list(int **list);
int		init_cmd(t_cmds *cmd);

char	**get_path(char **env);
char	**make_envlist(char **env);

void	free_words(char **words);
void	free_cmds(t_cmds *cmds);
void	free_arg(t_arg *arg);

int		quotes_blockidx(char *str);
int		is_in_idx(char *str, char *catchs);
int		is_builtin(char *word);
int		is_redirection(char *word);
char	*get_wordcatch(char *str, char *catchs);

int		remove_quotes(char *str, int size);
int		rm_quotes_wordsize(char *str, char *catches, int *rm_quotes);

void	change_term(struct termios *term);
void	no_echoctl(struct termios *old_term);

void	sig_init(void);

#endif
