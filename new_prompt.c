/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:42:15 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/27 17:42:04 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*fail_free(t_cmds *cmds)
{
	free_cmds(cmds);
	return (NULL);
}

void	is_ctrl_d(char **line)
{
	if (!(*line) && !errno)
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[13C", STDOUT_FILENO);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		*line = ft_strdup("exit");
	}
	else if (!(*line) && errno)
		fail_malloc_exit();
}

t_cmds	*new_prompt(t_arg *arg)
{
	t_cmds			*cmds;
	char			*line;
	struct termios	old_term;

	cmds = NULL;
	no_echoctl(&old_term);
	errno = 0;
	line = readline("minishell $> ");
	change_term(&old_term);
	is_ctrl_d(&line);
	if (line)
	{
		arg->syntax = 0;
		parse_line(line, &cmds, arg);
		if (ft_strlen(line))
			add_history(line);
		free(line);
	}
	return (cmds);
}
