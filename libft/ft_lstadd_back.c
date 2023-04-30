/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:37:51 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/19 21:45:25 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*now;

	now = *lst;
	if (!now)
		*lst = new;
	else
	{
		while (now->next)
			now = now->next;
		now->next = new;
	}
}
