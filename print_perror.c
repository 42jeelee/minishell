/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:34:36 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 17:58:42 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_perror(char *str)
{
	if (str[0] == 0)
		write(2, ": ", 2);
	perror(str);
	return (1);
}
