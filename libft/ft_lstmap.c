/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:55:47 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 17:55:59 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*now;

	result = ft_lstnew((*f)(lst->content));
	if (!result)
		return (NULL);
	lst = lst->next;
	now = result;
	while (lst)
	{
		now->next = ft_lstnew((*f)(lst->content));
		if (!now->next)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		now = now->next;
		lst = lst->next;
	}
	return (result);
}
