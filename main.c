/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:40:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/27 17:57:21 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	g_arg;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_arg.stat_loc = 1;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_cmds	*cmds;

	if (ac > 1)
		(void)av;
	if (init_shell(&(g_arg), env))
		return (print_perror("MINISHELL"));
	while (1)
	{
		cmds = new_prompt(&(g_arg));
		if (!(g_arg.syntax) && g_arg.num_of_cmd)
			(g_arg).stat_loc = exe_cmd_line(&(g_arg), cmds, &(g_arg).env);
		if (g_arg.syntax)
			g_arg.stat_loc = 258;
		free_cmds(cmds);
		(g_arg).num_of_cmd = 0;
	}
	free_arg(&g_arg);
	return (0);
}
