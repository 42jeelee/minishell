/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:06:34 by jeelee            #+#    #+#             */
/*   Updated: 2022/07/21 19:04:05 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_n(const char *str, int m)
{
	long long	n;

	n = 0;
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (n * m);
		if (n > 922337203685477580 || \
		(n == 922337203685477580 && *str - '0' > 7))
		{
			if (m == 1)
				return (-1);
			else
				return (0);
		}
		n *= 10;
		n += *str - '0';
		str++;
	}
	return (n * m);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	m;

	m = 1;
	while (*str == ' ' || (8 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m *= -1;
		str++;
	}
	n = get_n(str, m);
	return (n);
}
