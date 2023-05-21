/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdssize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:16:43 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 14:17:59 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	ft_cmdssize(t_cmds *cmds)
{
	int	size;

	size = 0;
	while (cmds)
	{
		size++;
		cmds = cmds->next;
	}
	return (size);
}
