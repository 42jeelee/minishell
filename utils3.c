/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:56:41 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/10 00:57:04 by jeelee           ###   ########.fr       */
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
