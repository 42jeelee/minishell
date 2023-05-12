/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:40:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/12 17:40:19 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmds	*cmds;
	t_arg	arg;

	if (ac > 1)
		(void)av;
	if (init_arg(&arg, env))
		return (print_perror("MINISHELL"));
	sig_init(&arg);
	if (!(arg.path))
		return (print_perror("MINISHELL"));
	while (1)
	{
		cmds = new_prompt(&(arg.num_of_cmd));
		if (!cmds)
			return (print_perror("MINISHELL"));
		if (trim_cmds(cmds, &arg))
			return (1);
		if (arg.num_of_cmd)
			arg.stat_loc = exe_cmd_line(&arg, cmds, &arg.env);
		free_cmds(cmds);
		arg.num_of_cmd = 0;
	}
	free_words(arg.path);
	return (0);
}
