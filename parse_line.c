/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:48:37 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/25 14:45:55 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fail_malloc_commands(char **commands)
{
	free_words(commands);
	return (-1);
}

static int	commands_size(char *line)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == '|')
			i++;
		if (line[i])
		{
			c++;
			while (line[i] && line[i] != '|')
			{
				i += quotes_blockidx(line + i);
				i++;
			}
		}
	}
	return (c);
}

static char	*get_command_foridx(char *line, int *d)
{
	char	*command;
	int		i;
	int		size;

	command = NULL;
	i = *d;
	while (line[i])
	{
		while (line[i] && line[i] == '|')
			i++;
		if (line[i])
		{
			size = is_in_idx(line + i, "|");
			if (size == -1)
				size = ft_strlen(line + i);
			command = ft_stridxdup(line, i, i + size);
			if (!command)
				return (NULL);
			*d = i + size;
			break ;
		}
		i++;
	}
	return (command);
}

static char	**split_commands(char *line)
{
	char	**commands;
	int		i;
	int		d;
	int		size;

	d = 0;
	size = commands_size(line);
	commands = (char **)malloc(sizeof(char *) * (size + 1));
	if (!commands)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		commands[i] = get_command_foridx(line, &d);
		if (!commands[i])
		{
			free_words(commands);
			return (NULL);
		}
	}
	commands[i] = 0;
	return (commands);
}

int	parse_line(char *line, t_cmds **cmds, t_arg *arg)
{
	char	**commands;
	t_cmds	*n_cmd;
	int		size;
	int		i;

	commands = split_commands(line);
	if (!commands)
		return (-1);
	size = 0;
	while (commands[size])
		size++;
	arg->num_of_cmd = size;
	if (!size)
		size = 1;
	i = -1;
	while (++i < size)
	{
		n_cmd = new_cmd(&(commands[i]), arg);
		if (!n_cmd)
			return (fail_malloc_commands(commands));
		add_cmd_list(n_cmd, cmds);
	}
	free_words(commands);
	return (0);
}
