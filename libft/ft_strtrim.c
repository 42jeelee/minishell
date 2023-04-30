/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 18:26:00 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 19:48:14 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(size_t start, char const *s1, char const *set)
{
	size_t	len;
	size_t	end;

	len = 0;
	end = ft_strlen(s1);
	while (end && s1[end - 1] && ft_strchr(set, s1[end - 1]))
		end--;
	if (end <= start)
		len = 0;
	else
		len = end - start;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	start;
	size_t	len;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	len = get_len(start, s1, set);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s1[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}
