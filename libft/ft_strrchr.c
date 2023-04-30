/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:15:41 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 20:29:18 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = len;
	while (--i >= 0 && i < len)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
	}
	if (!c)
		return ((char *)(s + len));
	return (NULL);
}
