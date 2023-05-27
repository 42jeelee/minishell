/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:24:37 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/28 02:55:16 by jeelee           ###   ########.fr       */
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
	t_cmds	*now;
	t_cmds	*tmp;

	now = cmds;
	while (now)
	{
		if (now->cmd)
			free_words(now->cmd);
		if (now->redir_type)
			free(now->redir_type);
		if (now->file)
			free_words(now->file);
		tmp = now;
		now = now->next;
		free(tmp);
	}
	cmds = 0;
}

void	free_arg(t_arg *arg)
{
	free_words(arg->env);
	free(arg->pwd);
}

void	fail_malloc_exit(void)
{
	if (errno)
		print_perror("MINISHELL");
	exit(1);
}
