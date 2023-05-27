/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvalue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:37:36 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/28 03:05:39 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fail_malloc_free(char *word)
{
	free(word);
	return (1);
}

static void	copy_list_idxben(char **new_list, \
				char **old_list, int idx, int size)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	if (0 <= idx && idx < size)
	{
		while (++i < size)
		{
			if (idx != i)
				new_list[i] = old_list[j++];
		}
	}
	else
	{
		while (++i < size)
			new_list[i] = old_list[i];
	}
}

int	add_idx_wordlist(char *word, int idx, char ***list)
{
	char	**new_list;
	char	*worddup;
	int		size;

	worddup = ft_strdup(word);
	if (!worddup)
		return (1);
	size = 0;
	if (*list)
		while ((*list)[size])
			size++;
	new_list = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_list)
		return (fail_malloc_free(worddup));
	copy_list_idxben(new_list, *list, idx, size);
	if (0 <= idx && idx < size)
		new_list[idx] = worddup;
	else
		new_list[size] = worddup;
	new_list[size + 1] = 0;
	if (*list)
		free(*list);
	*list = new_list;
	return (0);
}

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
		if (add_idx_wordlist(tmp, 20, env))
			return (1);
		free(tmp);
	}
	else
	{
		free((*env)[i]);
		(*env)[i] = tmp;
	}
	return (0);
}
