/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:48:37 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/06 17:52:53 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_line(char *line, t_cmds **cmds, int *num_of_cmd)
{
	char	**commands;
	t_cmds	*n_cmd;
	int		size;
	int		i;

	commands = ft_split(line, '|');
	if (!commands)
		return (-1);
	size = 0;
	while (commands[size])
		size++;
	*num_of_cmd = size;
	if (!size)
		size = 1;
	i = -1;
	while (++i < size)
	{
		n_cmd = new_cmd(commands[i]);
		add_cmd_list(n_cmd, cmds);
	}
	free_words(commands);
	return (0);
}
