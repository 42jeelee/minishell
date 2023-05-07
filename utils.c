/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:57:42 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/07 12:48:58 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_list(char **new_list, char **old_list, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		new_list[i] = old_list[i];
}

int	add_list_word(char *word, char ***list)
{
	char	**new_list;
	char	*worddup;
	int		size;

	worddup = ft_strdup(word);
	if (!worddup)
		return (-1);
	size = 0;
	if (*list)
		while ((*list)[size])
			size++;
	new_list = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_list)
	{
		free(worddup);
		return (-1);
	}
	copy_list(new_list, *list, size);
	new_list[size] = worddup;
	new_list[size + 1] = 0;
	if (*list)
		free(*list);
	*list = new_list;
	return (0);
}

int	add_list_int(int num, int **list)
{
	int	*new_list;
	int	size;
	int	i;

	size = 0;
	if (*list)
		while ((*list)[size])
			size++;
	new_list = (int *)malloc(sizeof(int) * (size + 2));
	if (!new_list)
		return (-1);
	i = -1;
	while (++i < size)
		new_list[i] = (*list)[i];
	new_list[i] = num;
	new_list[i + 1] = 0;
	if (*list)
		free(*list);
	*list = new_list;
	return (0);
}

int	create_word_list(char ***list)
{
	*list = (char **)malloc(sizeof(char *));
	if (!(*list))
		return (-1);
	(*list)[0] = 0;
	return (0);
}

int	create_int_list(int **list)
{
	*list = (int *)malloc(sizeof(int));
	if (!(*list))
		return (-1);
	**list = 0;
	return (0);
}
