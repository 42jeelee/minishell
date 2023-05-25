/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:06 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/25 17:35:42 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_arg(t_arg *arg, char **env)
{
	arg->env = make_envlist(env);
	if (!arg->env)
		return (1);
	arg->num_of_cmd = 0;
	arg->stat_loc = 0;
	arg->pwd = 0;
	if (set_g_pwd(arg))
		return (1);
	return (0);
}

int	init_cmd(t_cmds *cmd)
{
	ft_memset(cmd, 0, sizeof(t_cmds));
	if (create_int_list(&(cmd->redir_type)) == -1)
		return (-1);
	if (create_word_list(&(cmd->file)) == -1)
		return (-1);
	if (create_word_list(&(cmd->cmd)))
		return (-1);
	cmd->next = 0;
	cmd->prev = 0;
	return (0);
}

int	init_shell(t_arg *arg, char **env)
{
	char	*shlvl;

	if (init_arg(arg, env))
		return (1);
	sig_init();
	shlvl = ft_itoa(ft_atoi(get_value_env("SHLVL", 5, arg->env)) + 1);
	if (!shlvl[0] || shlvl[0] == '0')
		return (1);
	if (set_valueenv("SHLVL", shlvl, arg->env))
		return (1);
	free(shlvl);
	return (0);
}

void	bi_init(char *word, t_blockinfo *bi)
{
	bi->word_size = ft_strlen(word);
	bi->start = 0;
	bi->end = 0;
	bi->quotes = 0;
	bi->quotes_start = -1;
}
