/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:03:54 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/21 19:29:03 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rm_quotes_word(char **word, t_blockinfo *bi)
{
	char	*change_word;

	if (bi->quotes)
	{
		change_word = rmbothend_str(*word, bi->start, bi->end);
		if (!change_word)
			return (1);
		free(*word);
		*word = change_word;
		bi->end -= 1;
		bi->word_size -= 2;
	}
	return (0);
}

int	rm_quotes_intoken(char **token, int i)
{
	t_blockinfo	bi;

	bi.start = i;
	while ((*token)[bi.start])
	{
		bi.start = str_in_idx(*token + i, "\'\"");
		if (bi.start == -1)
			break ;
		bi.quotes = (*token)[i + bi.start];
		bi.start += i + 1;
		bi.end = get_block_size(*token + bi.start, bi.quotes);
		if (bi.end > 0)
		{
			bi.end += bi.start;
			if (rm_quotes_word(token, &bi))
				return (1);
		}
		bi.start = bi.end;
	}
	return (0);
}

int	change_block(char **word, t_blockinfo *bi, t_arg *arg)
{
	int	block_size;

	block_size = bi->end - bi->start;
	if (block_size > 0 && change_block_env(word, bi, arg))
		return (1);
	return (0);
}

int	trim_word(char **word, t_arg *arg)
{
	t_blockinfo	bi;

	if (!(*word))
		return (0);
	bi.word_size = ft_strlen(*word);
	bi.start = 0;
	bi.quotes = 0;
	while ((*word)[bi.start])
	{
		bi.end = get_block_size(*word + bi.start, bi.quotes);
		if (bi.end == 0 && !bi.quotes)
		{
			bi.quotes = (*word)[bi.start];
			bi.start += 1;
		}
		else
		{
			bi.end += bi.start;
			if (change_block(word, &bi, arg))
				return (1);
			bi.quotes = 0;
			bi.start = bi.end;
		}
	}
	return (0);
}
