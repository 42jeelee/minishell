/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:16:32 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/27 17:29:54 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_list_size(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

t_cmds	*get_empty_cmd(void)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	if (init_cmd(cmd))
	{
		free_cmds(cmd);
		return (NULL);
	}
	return (cmd);
}

void	add_empty_cmd(t_arg *arg, t_cmds **cmds)
{
	t_cmds	*empty_cmd;

	empty_cmd = get_empty_cmd();
	if (!empty_cmd)
		fail_malloc_exit();
	add_cmd_list(empty_cmd, arg, cmds);
}

void	add_new_cmd(char **command, t_arg *arg, t_cmds **cmds)
{
	t_cmds	*n_cmd;

	n_cmd = new_cmd(command, arg);
	if (!n_cmd)
		fail_malloc_exit();
	add_cmd_list(n_cmd, arg, cmds);
}

int	is_syntax_error(char **commands, t_arg *arg)
{
	int	i;
	int	empty_command;

	empty_command = 0;
	i = -1;
	while (commands[++i])
	{
		if (is_empty_str(commands[i]))
			empty_command = 1;
		if (i > 0 && empty_command)
		{
			arg->num_of_cmd = 0;
			ft_putstr_fd(\
				"syntax error near unexpected token `|'\n", STDERR_FILENO);
			return (1);
		}
	}
	if (!i)
	{
		arg->num_of_cmd = 0;
		ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
