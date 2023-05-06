/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:40:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/06 18:38:54 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmds	*cmds;
	t_arg	*arg;
	char	**paths;
	int		num_of_cmds;

	if (ac > 1)
		(void)av;
	paths = get_path(env);
	while (1)
	{
		num_of_cmds = 0;
		cmds = new_prompt(&num_of_cmds);
		if (!cmds)
			ft_putendl_fd("ERROR!", 1);
		arg = get_arg(num_of_cmds, paths);
		if (!arg)
			ft_putendl_fd("ERROR!", 1);
		print_cmds(arg, cmds);
		// if (num_of_cmds)
		// 	exe_cmd_line(arg, cmds, env);
		free_cmds(cmds);
	}
	free_arg(arg);
	return (0);
}
