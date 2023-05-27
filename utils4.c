/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:08:39 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/27 18:53:28 by jeelee           ###   ########.fr       */
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
	if (!find_key_env("OLDPWD", env))
	{
		if (add_list_word("OLDPWD", &env_list) == -1)
		{
			free_words(env_list);
			return (NULL);
		}
	}
	return (env_list);
}

char	*ft_strchange(char *str, int st, int end, char *changestr)
{
	char	*new_str;
	int		s_size;
	int		c_size;
	int		i;

	if (st > end)
		return (str);
	s_size = ft_strlen(str);
	if (st < 0 || s_size < end)
		return (str);
	c_size = ft_strlen(changestr);
	new_str = (char *)malloc(sizeof(char) * (s_size - (end - st) + c_size + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < st)
		new_str[i] = str[i];
	i = -1;
	while (++i < c_size)
		new_str[st + i] = changestr[i];
	i = -1;
	while (++i < s_size - end)
		new_str[st + c_size + i] = str[end + i];
	new_str[st + c_size + i] = 0;
	return (new_str);
}

char	*ft_tristrjoin(char *s1, char *s2, char *s3)
{
	char	*str;
	int		s1_size;
	int		s2_size;
	int		s3_size;
	int		i;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	s3_size = ft_strlen(s3);
	str = (char *)malloc(sizeof(char) * (s1_size + s2_size + s3_size + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < s1_size)
		str[i] = s1[i];
	i = -1;
	while (++i < s2_size)
		str[s1_size + i] = s2[i];
	i = -1;
	while (++i < s3_size)
		str[s1_size + s2_size + i] = s3[i];
	str[s1_size + s2_size + i] = 0;
	return (str);
}

char	*rmbothend_str(char *word, int start, int end)
{
	char	*new_str;
	int		size;
	int		word_i;
	int		i;

	size = ft_strlen(word) - 2;
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	word_i = 0;
	i = -1;
	while (++i < size)
	{
		while (word_i == start - 1 || word_i == end)
			word_i++;
		new_str[i] = word[word_i];
		word_i++;
	}
	new_str[i] = 0;
	return (new_str);
}
