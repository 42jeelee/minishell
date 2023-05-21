/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvalue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:37:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/21 21:19:50 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_valueenv(char *key, char *value, char **env)
{
	int		i;
	int		key_size;
	char	*tmp;

	if (!key || !key)
		return (0);
	if (!value)
		value = "";
	key_size = ft_strlen(key);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(key, env[i], key_size))
		{
			tmp = ft_tristrjoin(key, "=", value);
			if (!tmp)
				return (1);
			free(env[i]);
			env[i] = tmp;
			break ;
		}
	}
	return (0);
}
