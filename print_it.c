/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:13:33 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/21 15:50:12 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_redirection(int *type, char **filenames)
{
	int	i;

	i = -1;
	while (type[++i])
		printf("TYPE: %d\nfile: %s\n", type[i], filenames[i]);
}

void	print_words(char **words)
{
	int	i;

	if (words)
	{
		i = -1;
		while (words[++i])
			printf("[%d]: %s\n", i, words[i]);
	}
}

void	print_arg(t_arg *arg)
{
	printf("++++++++++ARG+++++++++++++\n");
	printf("num_of_cmds: %d\n", arg->num_of_cmd);
	printf("++++++++++++++++++++++++++\n");
}

void	print_cmds(t_arg *arg, t_cmds *cmds)
{
	int	i;

	if (!arg)
	{
		printf("arg is NULL\n");
		return ;
	}
	if (!cmds)
	{
		printf("cmds is NULL\n");
		return ;
	}
	i = -1;
	while (++i < arg->num_of_cmd)
	{
		printf("--------[ %d ]---------\n", i);
		if (cmds->redir_type)
		{
			printf("REDIRECTION:\n");
			print_redirection(cmds->redir_type, cmds->file);
		}
		printf("builtin: %d\n", cmds->builtin);
		print_words(cmds->cmd);
		printf("-----------------------\n");
		cmds = cmds->next;
	}
}
