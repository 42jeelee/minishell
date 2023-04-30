/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:35:25 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/19 17:10:34 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dl;
	size_t	sl;

	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	if (dl >= dstsize)
		return (sl + dstsize);
	i = 0;
	while (src[i] && dl + i < dstsize - 1)
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = 0;
	return (dl + sl);
}
