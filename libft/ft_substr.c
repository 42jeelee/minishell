/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:03:41 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 20:56:57 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	slen;
	size_t	size;

	slen = ft_strlen(s);
	if (start > slen)
		size = 0;
	else if (slen - start < len)
		size = slen - start;
	else
		size = len;
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	if (slen >= start)
	{
		ft_strlcpy(result, s + start, size + 1);
	}
	else
		ft_bzero(result, size + 1);
	return (result);
}
