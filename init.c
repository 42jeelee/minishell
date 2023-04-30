/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:29:06 by jeelee            #+#    #+#             */
/*   Updated: 2023/04/30 21:36:39 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fail_malloc(t_cmds *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->in_redir_type)
		free(cmd->in_redir_type);
	if (cmd->out_redir_type)
		free(cmd->out_redir_type);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	return (-1);
}

int	init_cmd(t_cmds *cmd)
{
	ft_memset(cmd, 0, sizeof(t_cmds));
	if (create_int_list(&(cmd->in_redir_type)) == -1)
		return (-1);
	if (create_int_list(&(cmd->out_redir_type)) == -1)
		return (fail_malloc(cmd));
	if (create_word_list(&(cmd->infile)) == -1)
		return (fail_malloc(cmd));
	if (create_word_list(&(cmd->outfile)) == -1)
		return (fail_malloc(cmd));
	if (create_word_list(&(cmd->cmd)))
		return (fail_malloc(cmd));
	return (0);
}
