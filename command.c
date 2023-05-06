/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:40:55 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/06 18:42:09 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_any_list(int type, char *word, t_cmds *cmd)
{
	if (type)
	{
		if (add_list_int(type, &(cmd->redir_type)) == -1)
			return (-1);
		if (add_list_word(word, &(cmd->file)) == -1)
			return (-1);
	}
	else
	{
		if (!(*(cmd->cmd)))
			cmd->builtin = is_builtin(word);
		if (add_list_word(word, &(cmd->cmd)) == -1)
			return (-1);
	}
	return (0);
}

int	put_word_inlist(char *command, int *i, int type, t_cmds *cmd)
{
	char	*word;
	int		size;
	int		rm_quotes;

	size = rm_quotes_wordsize(command + *i, "< >", &rm_quotes);
	if (size > 0 || rm_quotes)
	{
		word = get_wordcatch(command + *i, "< >");
		if (!word)
			return (-1);
		if (add_any_list(type, word, cmd) == -1)
			return (-1);
		free(word);
	}
	*i += size + rm_quotes;
	return (0);
}

int	parse_cmd(t_cmds *cmd, char *command)
{
	int	i;
	int	type;

	if (!command)
		return (0);
	type = 0;
	i = 0;
	while (command[i])
	{
		while (command[i] == ' ')
			i++;
		if (put_word_inlist(command, &i, type, cmd) == -1)
			return (-1);
		type = is_redirection(command + i);
		if (type)
			i += (type & 1) + 1;
	}
	return (0);
}

t_cmds	*new_cmd(char *commad)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	if (parse_cmd(cmd, commad) == -1)
	{
		free_cmds(cmd);
		return (NULL);
	}
	return (cmd);
}

void	add_cmd_list(t_cmds *new, t_cmds **list)
{
	t_cmds	*tmp;

	if (!(*list))
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
