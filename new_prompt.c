/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:42:15 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/06 17:50:32 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*new_prompt(int *num_of_cmd)
{
	t_cmds	*cmds;
	char	*line;
	int		status;

	cmds = NULL;
	line = readline("minishell $> ");
	if (line)
	{
		status = parse_line(line, &cmds, num_of_cmd);
		add_history(line);
		free(line);
		if (status == -1)
		{
			free(cmds);
			return (NULL);
		}
	}
	return (cmds);
}
