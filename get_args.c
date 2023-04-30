/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:56:20 by jeelee            #+#    #+#             */
/*   Updated: 2023/04/30 17:46:45 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	char	**paths;

	paths = NULL;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
		{
			paths = ft_split(*env, ':');
			if (!paths)
				return (NULL);
			break ;
		}
		env++;
	}
	return (paths);
}

t_arg	*get_arg(int num_of_cmd, char **paths)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->num_of_cmd = num_of_cmd;
	arg->path = paths;
	return (arg);
}
