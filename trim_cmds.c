/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:03:54 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/24 15:07:32 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_init(char *word, t_blockinfo *bi)
{
	bi->word_size = ft_strlen(word);
	bi->start = 0;
	bi->end = 0;
	bi->quotes = 0;
}

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

int	change_block(char **word, t_blockinfo *bi, t_arg *arg, int flag)
{
	int	block_size;

	block_size = bi->end - bi->start;
	if (flag && arg)
	{
		if (block_size > 0 && change_block_env(word, bi, arg))
			return (1);
	}
	else if (!flag)
	{
		if (bi->quotes && rm_quotes_word(word, bi))
			return (1);
		bi->quotes = 0;
	}
	return (0);
}

int	trim_word(char **word, t_arg *arg, int flag)
{
	t_blockinfo	bi;

	if (!(*word))
		return (0);
	bi_init(*word, &bi);
	while ((*word)[bi.start])
	{
		bi.end = get_block_size(*word + bi.start, bi.quotes);
		if (bi.end == 0)
		{
			if (!bi.quotes)
				bi.quotes = (*word)[bi.start];
			else
				bi.quotes = 0;
			bi.start += 1;
		}
		else
		{
			bi.end += bi.start;
			if (change_block(word, &bi, arg, flag))
				return (1);
			bi.start = bi.end;
		}
	}
	return (0);
}
