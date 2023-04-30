/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:33:49 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/17 17:38:38 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;
	size_t			i;

	result = (unsigned char *)malloc(count * size);
	if (!result)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}
