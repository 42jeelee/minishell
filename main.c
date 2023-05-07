/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:40:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/07 13:55:32 by jeelee           ###   ########.fr       */
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
	if (!(arg.path))
		print_perror("PARSE ERROR");
	while (1)
	{
		cmds = new_prompt(&(arg.num_of_cmd));
		if (!cmds)
			print_perror("PARSE ERROR");
		if (arg.num_of_cmd)
			exe_cmd_line(&arg, cmds, env);
		free_cmds(cmds);
		arg.num_of_cmd = 0;
	}
	free_words(arg.path);
	return (0);
}
