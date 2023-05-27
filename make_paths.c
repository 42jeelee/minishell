/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:38:09 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/27 20:13:53 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static char		**path_split(char const *s, char c);
static size_t	how_many_chunk(char const *str, char c);
static char		**make_strs(char **strs, char const *str, char c, size_t size);
static char		**make_allfree(char **strs, size_t y);

char	**make_paths(char **env)
{
	int		i;
	char	*compare;
	char	**strs;
	char	*oneline;

	i = -1;
	compare = "PATH=";
	while (env[++i])
		if (ft_strncmp(env[i], compare, 5) == 0)
			break ;
	if (env[i] == 0)
		return (0);
	oneline = ft_strdup(env[i] + 5);
	if (oneline == 0)
		exit(1);
	strs = path_split(oneline, ':');
	if (strs == 0)
		exit(1);
	free(oneline);
	return (strs);
}

static char	**path_split(char const *s, char c)
{
	size_t	size;
	char	**strs;

	size = how_many_chunk(s, c);
	strs = (char **)malloc(sizeof(char *) * (size + 1));
	if (strs == 0)
		return (0);
	return (make_strs(strs, s, c, size));
}

static char	**make_strs(char **strs, char const *str, char c, size_t size)
{
	size_t	x;
	size_t	y;
	size_t	i;

	y = 0;
	while (y < size)
	{
		x = 0;
		i = 0;
		while (*str && *str == c)
			str++;
		while (str[i] && str[i] != c)
			i++;
		strs[y] = (char *)malloc(sizeof(char) * (i + 2));
		if (strs[y] == 0)
			return (make_allfree(strs, y));
		while (i--)
			strs[y][x++] = *(str++);
		strs[y][x++] = '/';
		strs[y][x] = '\0';
		y++;
	}
	strs[y] = 0;
	return (strs);
}

static size_t	how_many_chunk(char const *str, char c)
{
	size_t	count;
	int		on;

	on = 0;
	count = 0;
	while (*str)
	{
		if (*str != c && on == 0)
		{
			count++;
			on = 1;
		}
		else if (*str == c && on == 1)
			on = 0;
		str++;
	}
	return (count);
}

static char	**make_allfree(char **strs, size_t y)
{
	size_t	i;

	i = 0;
	while (i < y)
		free(strs[i++]);
	free(strs);
	return (0);
}
