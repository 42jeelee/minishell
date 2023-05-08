/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:08:39 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/09 01:07:57 by jeelee           ###   ########.fr       */
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
	if (!getenv("OLDPWD"))
	{
		if (add_list_word("OLDPWD", &env_list) == -1)
		{
			free_words(env_list);
			return (NULL);
		}
	}
	return (env_list);
}

char	*ft_strchange(char *str, int start, int end, char *changestr)
{
	char	*new_str;
	int		s_size;
	int		c_size;
	int		i;

	if (start > end)
		return (str);
	s_size = ft_strlen(str);
	if (start < 0 || s_size < end)
		return (str);
	c_size = ft_strlen(changestr);
	new_str = (char *)malloc(sizeof(char) * (s_size - (end - start) + c_size));
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < start)
		new_str[i] = str[i];
	i = -1;
	while (++i < c_size)
		new_str[start + i] = changestr[i];
	i = -1;
	while (++i < s_size - end)
		new_str[start + c_size + i] = str[end + i];
	new_str[start + c_size + i] = 0;
	return (new_str);
}
