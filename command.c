/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:40:55 by jeelee            #+#    #+#             */
/*   Updated: 2023/04/30 21:36:34 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *word)
{
	int	size;

	size = ft_strlen(word);
	if (size > 2)
		return (0);
	else if (size == 2)
	{
		if (word[0] == '<' && word[1] == '<')
			return (1);
		else if (word[0] == '>' && word[1] == '>')
			return (3);
	}
	else if (size == 1)
	{
		if (word[0] == '<')
			return (2);
		else if (word[0] == '>')
			return (4);
	}
	return (0);
}

int	parse_redirection(char *type, char *filename, t_cmds *cmd)
{
	int	typenum;

	if (!filename)
		return (-1);
	typenum = is_redirection(type);
	if (typenum < 3)
	{
		if (add_list_int((typenum & 1) + 1, &(cmd->in_redir_type)) == -1)
			return (-1);
		if (add_list_word(filename, &(cmd->infile)) == -1)
			return (-1);
	}
	else
	{
		if (add_list_int((typenum & 1) + 1, &(cmd->out_redir_type)) == -1)
			return (-1);
		if (add_list_word(filename, &(cmd->outfile)) == -1)
			return (-1);
	}
	return (0);
}

int	parse_cmd(t_cmds *cmd, char *command)
{
	char	**words;
	int		i;

	words = ft_split(command, ' ');
	if (!words)
		return (-1);
	i = -1;
	while (words[++i])
	{
		if (is_redirection(words[i]))
		{
			if (parse_redirection(words[i], words[i + 1], cmd) == -1)
			{
				free_words(words);
				return (-1);
			}
			i++;
		}
		else
			add_list_word(words[i], &(cmd->cmd));
	}
	free_words(words);
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
		free(cmd);
		return (NULL);
	}
	cmd->next = 0;
	cmd->prev = 0;
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
