/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_free_things.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:42:18 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 19:42:48 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	free_things(void *a, void *b, void *c, void *d)
{
	if (a != 0)
		free(a);
	if (b != 0)
		free(b);
	if (c != 0)
		free(c);
	if (d != 0)
		free(d);
	return (1);
}
