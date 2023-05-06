/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:15:27 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/06 15:29:10 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_idx(char *str, char *catchs)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		i += quotes_blockidx(str + i);
		if (ft_strchr(catchs, str[i]))
			return (i);
	}
	return (-1);
}

char	*get_wordcatch(char *str, char *catchs)
{
	char	*word;
	int		i;
	int		size;
	int		rm_quotes;

	size = rm_quotes_wordsize(str, catchs, &rm_quotes);
	if (!size)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		if (rm_quotes && (*str == '\'' || *str == '\"'))
		{
			rm_quotes--;
			str++;
		}
		word[i] = *str;
		str++;
	}
	word[i] = 0;
	return (word);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

int	is_builtin(char *word)
{
	const char	*builtins[8] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", 0};
	int			i;

	i = -1;
	while (builtins[++i])
	{
		if (!ft_strcmp(word, builtins[i]))
			return (1);
	}
	return (0);
}
