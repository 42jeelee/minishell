/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:28:25 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/20 14:28:27 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

int	compare_two_env(char *s1, char *s2);

void	sort_export(char **copied_env)
{
	int		size;
	char	*tmp;
	int		i;
	int		j;

	size = 0;
	while (copied_env[size])
		size++;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (copied_env[j + 1] != 0)
		{
			if (compare_two_env(copied_env[j], copied_env[j + 1]) > 0)
			{
				tmp = copied_env[j];
				copied_env[j] = copied_env[j + 1];
				copied_env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	compare_two_env(char *s1, char *s2)
{
	int	s1_size;
	int	s2_size;
	int	n;
	int	out;

	s1_size = str_size_until_equal_or_null(s1);
	s2_size = str_size_until_equal_or_null(s2);
	if (s1_size <= s2_size)
		n = s1_size;
	else
		n = s2_size;
	out = ft_strncmp(s1, s2, n);
	if (out == 0)
	{
		if (s1[n] == '=' || s1[n] == '\0')
			return (0);
		if (s2[n] == '=' || s2[n] == '\0')
			return (1);
	}
	return (out);
}

void	print_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if ((env[i][0] == '_' && env[i][1] == '=') ||
				(env[i][0] == '_' && env[i][1] == '\0'))
			i++;
		else
		{
			j = 0;
			write(1, "declare -x ", 11);
			while (env[i][j] && env[i][j] != '=')
				write(1, &env[i][j++], 1);
			if (env[i][j] == '=')
			{
				write(1, "=\"", 2);
				write(1, env[i] + j + 1, strlen(env[i] + j + 1));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
			i++;
		}
	}
}
