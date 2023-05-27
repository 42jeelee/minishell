/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:48:37 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/27 19:11:15 by jeelee           ###   ########.fr       */
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

	if (!line)
		return (1);
	c = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			c++;
		i += quotes_blockidx(line + i);
		i++;
	}
	return (c);
}

static char	*get_command_foridx(char *line, int *d)
{
	char	*command;
	char	*chars;

	chars = NULL;
	command = NULL;
	if (*d > 0 && line[*d] && line[*d] == '|')
		(*d)++;
	if (!is_empty_command(line + *d))
		chars = " ";
	command = current_command(line, d, chars);
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
	int		size;
	int		i;

	commands = split_commands(line);
	if (!commands)
		fail_malloc_exit();
	size = get_list_size(commands);
	if (!size)
		size = 1;
	if (is_syntax_error(commands))
	{
		add_empty_cmd(arg, cmds);
		arg->num_of_cmd = 0;
		return (0);
	}
	i = -1;
	while (++i < size)
		add_new_cmd(&(commands[i]), arg, cmds);
	free_words(commands);
	return (0);
}
