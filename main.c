/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:40:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/22 16:20:16 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmds	*cmds;
	t_arg	arg;

	if (ac > 1)
		(void)av;
	if (init_shell(&arg, env))
		return (print_perror("MINISHELL"));
	while (1)
	{
		cmds = new_prompt(&arg);
		if (!cmds)
			return (print_perror("MINISHELL"));
		if (arg.num_of_cmd)
			exe_cmd_line(&arg, cmds, &arg.env);
		free_cmds(cmds);
		arg.num_of_cmd = 0;
	}
	return (0);
}
