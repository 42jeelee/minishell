/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvalue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:37:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/28 02:04:38 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_valueenv(char *key, char *value, char ***env)
{
	int		i;
	char	*tmp;

	if (!key || !(key[0]))
		return (0);
	if (!value)
		value = "";
	tmp = ft_tristrjoin(key, "=", value);
	if (!tmp)
		return (1);
	i = find_key_env(key, *env);
	if (i == -1)
	{
		if (add_list_word(tmp, env))
			return (1);
	}
	else
	{
		free((*env)[i]);
		(*env)[i] = tmp;
	}
	return (0);
}
