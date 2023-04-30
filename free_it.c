/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:24:37 by jeelee            #+#    #+#             */
/*   Updated: 2023/04/30 17:28:49 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_words(char **words)
{
	int	i;

	if (words)
	{
		i = -1;
		while (words[++i])
			free(words[i]);
		free(words);
		words = 0;
	}
}

void	free_cmds(t_cmds *cmds)
{
	if (cmds)
	{
		if (cmds->cmd)
			free_words(cmds->cmd);
		if (cmds->in_redir_type)
			free(cmds->in_redir_type);
		if (cmds->infile)
			free_words(cmds->infile);
		if (cmds->out_redir_type)
			free(cmds->out_redir_type);
		if (cmds->outfile)
			free_words(cmds->outfile);
		cmds = 0;
	}
}

void	free_arg(t_arg *arg)
{
	if (arg)
	{
		if (arg->path)
			free_words(arg->path);
		free(arg);
		arg = 0;
	}
}
