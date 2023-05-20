/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_str_idx_in_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:28:33 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/20 14:28:34 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

int	find_str_idx_in_env(char *str, char **env)
{
	int	i;
	int	size;

	i = 0;
	size = str_size_until_equal_or_null(str);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], size) == 0 &&
				(env[i][size] == '=' || env[i][size] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
