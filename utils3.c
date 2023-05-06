/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:56:41 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/06 15:29:25 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *word)
{
	if (word[0] == '<' && word[1] == '<')
		return (INTWO);
	else if (word[0] == '>' && word[1] == '>')
		return (OUTTWO);
	else if (word[0] == '<')
		return (INONE);
	else if (word[0] == '>')
		return (OUTONE);
	return (0);
}

int	quotes_blockidx(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		while (str[++i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				return (i);
		}
	}
	return (0);
}

int	remove_quotes(char *str, int size)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = -1;
	while (str[++i] && i < size)
	{
		if (str[i] == '\'' || str[i] == '\"')
			quotes++;
	}
	return ((quotes / 2) * 2);
}

int	rm_quotes_wordsize(char *str, char *catches, int *rm_quotes)
{
	int	size;
	int	rm;

	rm = 0;
	size = is_in_idx(str, catches);
	if (size == -1)
		size = ft_strlen(str);
	rm = remove_quotes(str, size);
	size -= rm;
	if (rm_quotes)
		*rm_quotes = rm;
	return (size);
}
