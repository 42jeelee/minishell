/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:08:39 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/08 20:28:15 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_dup(char **list)
{
	char	**new_list;
	int		i;
	int		size;

	size = 0;
	while (list[size])
		size++;
	new_list = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_list)
		return (NULL);
	i = -1;
	while (list[++i])
	{
		new_list[i] = ft_strdup(list[i]);
		if (!new_list[i])
		{
			free_words(new_list);
			return (NULL);
		}
	}
	new_list[i] = 0;
	return (new_list);
}

char	**make_envlist(char **env)
{
	char	**env_list;

	env_list = list_dup(env);
	if (!env_list)
		return (NULL);
	if (!get_value_env("OLDPWD", env))
	{
		if (add_list_word("OLDPWD", &env_list) == -1)
		{
			free_words(env_list);
			return (NULL);
		}
	}
	return (env_list);
}

char	*ft_strsizejoin(char *s1, int size, char *s2)
{
	char	*new_str;
	int		s1_size;
	int		s2_size;
	int		i;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if (s1_size < size)
		size = s1_size;
	new_str = (char *)malloc(sizeof(char) * (size + s2_size + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < size)
		new_str[i] = s1[i];
	i = -1;
	while (++i < s2_size)
		new_str[size + i] = s2[i];
	new_str[size + i] = 0;
	return (new_str);
}
