/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:59:34 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 18:25:31 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	size_t			i;

	if (!len || dst == src)
		return (dst);
	pdst = dst;
	psrc = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		if (src > dst)
			*(pdst + i) = *(psrc + i);
		else
			*(pdst + (len - i - 1)) = *(psrc + (len - i - 1));
		i++;
	}
	return (dst);
}
