/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:42:15 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/08 01:28:24 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_ctrl_d(char **line)
{
	if (!(*line) && !errno)
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[13C", STDOUT_FILENO);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		*line = ft_strdup("exit");
	}
}

t_cmds	*new_prompt(int *num_of_cmd)
{
	t_cmds			*cmds;
	char			*line;
	struct termios	old_term;
	int				status;

	no_echoctl(&old_term);
	cmds = NULL;
	line = readline("minishell $> ");
	change_term(&old_term);
	is_ctrl_d(&line);
	if (line)
	{
		status = parse_line(line, &cmds, num_of_cmd);
		add_history(line);
		free(line);
		if (status == -1)
		{
			free_cmds(cmds);
			return (NULL);
		}
	}
	return (cmds);
}
