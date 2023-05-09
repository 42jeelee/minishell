/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:40:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/08 20:07:53 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmds	*cmds;
	t_arg	arg;

	if (ac > 1)
		(void)av;
	arg.path = get_path(env);
	arg.env = make_envlist(env);
	sig_init(&arg);
	if (!(arg.path))
		print_perror("PARSE ERROR");
	while (1)
	{
		cmds = new_prompt(&(arg.num_of_cmd));
		if (!cmds)
			print_perror("PARSE ERROR");
		if (change_allist_env(cmds, &arg))
			return (1);
		if (arg.num_of_cmd)
			exe_cmd_line(&arg, cmds, &arg.env);
		free_cmds(cmds);
		arg.num_of_cmd = 0;
	}
	free_words(arg.path);
	return (0);
}
