/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:03:54 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/25 17:23:32 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_init(char *word, t_blockinfo *bi)
{
	bi->word_size = ft_strlen(word);
	bi->start = 0;
	bi->end = 0;
	bi->quotes = 0;
	bi->quotes_start = -1;
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
		bi->end -= 2;
		bi->word_size -= 2;
	}
	return (0);
}

int	change_env_block(char **word, t_blockinfo *bi, t_arg *arg)
{
	int	block_size;

	block_size = bi->end - bi->start;
	if (arg)
	{
		if (block_size > 0 && change_block_env(word, bi, arg))
			return (1);
	}
	return (0);
}

int	change_quotes_block(char **word, t_blockinfo *bi, t_arg *arg)
{
	(void)arg;
	if (bi->quotes && rm_quotes_word(word, bi))
		return (1);
	return (0);
}

int on_quotes(char **word, t_blockinfo *bi, \
			t_arg *arg, int (*f)(char**, t_blockinfo*, t_arg*))
{
	int	size;

	size = quotes_blockidx((*word) + bi->end);
	if (size)
	{
		if (bi->start < bi->end)
		{
			if (f(word, bi, arg))
				return (1);
		}
		bi->quotes_start = bi->end;
		bi->quotes = (*word)[bi->end];
		bi->start = bi->end + 1;
		bi->end += size;
		if (f(word, bi, arg))
			return (1);
		bi->quotes = 0;
		bi->quotes_start = -1;
		bi->start = bi->end + 1;
	}
	return (0);
}

int change_trim_block(char **word, t_arg *arg, \
					int (*f)(char**, t_blockinfo*, t_arg*))
{
	t_blockinfo	bi;

	if (!(*word))
		return (0);
	bi_init(*word, &bi);
	while ((*word)[bi.end])
	{
		if (on_quotes(word, &bi, arg, f))
			return (1);
		(bi.end)++;
	}
	if (bi.start < bi.end)
	{
		if (f(word, &bi, arg))
			return (1);
	}
	return (0);
}
