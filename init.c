/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:06 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/12 17:33:16 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_arg(t_arg *arg, char **env)
{
	arg->path = get_path(env);
	if (!arg->path)
		return (1);
	arg->env = make_envlist(env);
	if (!arg->env)
		return (1);
	arg->num_of_cmd = 0;
	arg->stat_loc = 0;
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
