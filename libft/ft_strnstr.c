/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:46:47 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 20:38:54 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	m;

	if ((!(*haystack) && !(*needle)))
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i <= len)
	{
		m = 0;
		while (i + m < len && needle[m] && haystack[i + m] == needle[m])
			m++;
		if (!needle[m])
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
