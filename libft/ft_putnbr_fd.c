/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:08:34 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/19 19:09:39 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_nbrs(int n, int fd)
{
	if (n > 0)
	{
		put_nbrs(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		put_nbrs(-n, fd);
	}
	else
		put_nbrs(n, fd);
}
