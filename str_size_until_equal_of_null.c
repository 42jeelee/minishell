/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_size_until_equal_of_null.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:57:59 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/20 14:58:11 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	str_size_until_equal_or_null(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
