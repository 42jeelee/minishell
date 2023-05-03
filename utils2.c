/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:15:27 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/03 14:42:21 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_idx(char *str, char *catch)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(catch, str[i]))
			return (i);
	}
	return (-1);
}

char	*get_wordcatch(char *str, char *catch)
{
	char	*word;
	int		i;
	int		size;

	size = is_in_idx(str, catch);
	if (!size)
		return (NULL);
	if (size == -1)
		size = ft_strlen(str);
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < size)
		word[i] = str[i];
	word[i] = 0;
	return (word);
}
