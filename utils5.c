/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:16:22 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/26 18:45:41 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_command(char *command)
{
	int	i;
	int	size;

	size = is_in_idx(command, "|");
	if (size == -1)
		size = ft_strlen(command);
	i = -1;
	while (++i < size)
	{
		if (command[i] != ' ')
			return (0);
	}
	return (1);
}

char	*ft_stridxdup(char *str, int start, int end)
{
	char	*new;
	int		size;
	int		i;

	size = end - start;
	if (size <= 0)
		size = 1;
	new = (char *)malloc(sizeof(char) * size);
	if (!new)
		return (NULL);
	i = -1;
	while (++i < size)
		new[i] = (str + start)[i];
	new[i] = 0;
	return (new);
}

char	*ft_stridxduptrim(char *str, int start, int end, char *chars)
{
	char	*new;
	char	*trim_new;

	new = ft_stridxdup(str, start, end);
	if (!new)
		return (NULL);
	if (chars)
	{
		trim_new = ft_strtrim(new, chars);
		free(new);
	}
	else
		trim_new = new;
	return (trim_new);
}

char	*current_command(char *line, int *d, char *chars)
{
	char	*command;
	int		size;

	size = is_in_idx(line + *d, "|");
	if (size == 0)
	{
		*d += 1;
		return (ft_strdup(""));
	}
	if (size == -1)
		size = ft_strlen(line + *d);
	command = ft_stridxduptrim(line, *d, *d + size, chars);
	*d += size;
	return (command);
}
