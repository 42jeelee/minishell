/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:37:47 by byejeon           #+#    #+#             */
/*   Updated: 2023/04/30 21:38:04 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	out = malloc(sizeof(char) * (len + 1));
	if (out == 0)
		return (0);
	while (*s1)
		out[i++] = *(s1++);
	while (*s2)
		out[i++] = *(s2++);
	out[i] = '\0';
	return (out);
}
