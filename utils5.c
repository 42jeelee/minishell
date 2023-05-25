/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:16:22 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/25 02:24:46 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_stridxdup(char *str, int start, int end)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char) * (end - start));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < end - start)
		new[i] = (str + start)[i];
	new[i] = 0;
	return (new);
}
