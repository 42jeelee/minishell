/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:56:20 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/06 20:52:29 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	char	**paths;
	char	*tmp;
	int		i;

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
	i = -1;
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	return (paths);
}
