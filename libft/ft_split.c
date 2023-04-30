/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 18:51:25 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 21:01:44 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **result, size_t len)
{
	size_t	i;

	i = 0;
	while (i <= len)
		free(result[i]);
	free(result);
}

static size_t	word_count(char const *s, char c)
{
	size_t	cnt;
	char	*pre;
	char	*now;

	cnt = 0;
	if (!(*s))
		return (cnt);
	now = ft_strchr(s, c);
	if (s != now)
		cnt++;
	pre = now;
	while (now && *now)
	{
		now = ft_strchr(pre + 1, c);
		if (*(pre + 1) && now != pre + 1)
			cnt++;
		pre = now;
	}
	return (cnt);
}

static char	*put_word(char const *s, char c, size_t	*offset)
{
	char	*word;
	char	*end;
	size_t	len;

	while (*(s + *offset) == c)
		(*offset)++;
	end = ft_strchr(s + *offset, c);
	if (!end)
		len = ft_strlen(s + *offset);
	else
		len = end - (s + *offset);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, (s + *offset), len + 1);
	*offset += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	offset;
	size_t	wc;
	size_t	i;

	wc = word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!result)
		return (NULL);
	offset = 0;
	i = 0;
	while (i < wc)
	{
		result[i] = put_word(s, c, &offset);
		if (!result[i])
		{
			free_all(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = 0;
	return (result);
}
