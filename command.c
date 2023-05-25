/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:40:55 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/25 16:31:13 by jeelee           ###   ########.fr       */
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

int	put_word_inlist(char **command, int *i, int type, t_cmds *cmd)
{
	char	*word;
	int		size;

	size = is_in_idx(*command + *i, "< >");
	if (size == -1)
		size = ft_strlen(*command + *i);
	if (size > 0)
	{
		word = get_wordcatch(*command + *i, "< >");
		if (!word)
			return (-1);
		if (change_trim_block(&word, 0, change_quotes_block))
			return (-1);
		if (add_any_list(type, word, cmd) == -1)
			return (-1);
		free(word);
	}
	*i += size;
	return (0);
}

int	parse_cmd(t_cmds *cmd, char **command)
{
	int	i;
	int	type;

	if (!(*command))
		return (0);
	type = 0;
	i = 0;
	while ((*command)[i])
	{
		while ((*command)[i] == ' ')
			i++;
		if (put_word_inlist(command, &i, type, cmd) == -1)
			return (-1);
		type = is_redirection(*command + i);
		if (type)
			i += (type & 1) + 1;
	}
	return (0);
}

t_cmds	*new_cmd(char **command, t_arg *arg)
{
	t_cmds	*cmd;

	if (change_trim_block(command, arg, change_env_block))
		return (NULL);
	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	if (init_cmd(cmd))
		return (NULL);
	if (parse_cmd(cmd, command) == -1)
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
