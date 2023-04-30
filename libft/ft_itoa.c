/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:00:36 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 16:58:06 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(long long n)
{
	size_t		len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	set_num(long long nb, char *result_now)
{
	if (nb > 0)
	{
		*result_now = nb % 10 + '0';
		set_num(nb / 10, result_now - 1);
	}
}

static char	*is_zero(void)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * 2);
	if (!result)
		return (NULL);
	result[0] = '0';
	result[1] = 0;
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	long long	nb;
	size_t		len;

	nb = n;
	if (nb == 0)
		return (is_zero());
	len = get_len(nb);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		nb *= -1;
		result[0] = '-';
	}
	result[len] = 0;
	set_num(nb, result + len - 1);
	return (result);
}
