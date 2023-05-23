/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cmdenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:00:29 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/23 20:13:12 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env(char *key, int size, char **env)
{
	char	*value;
	int		i;

	if (size == 0)
		return (NULL);
	value = NULL;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(key, env[i], size) && env[i][size] == '=')
		{
			value = env[i] + size + 1;
			break ;
		}
	}
	return (value);
}

int	get_env_size(char *word, int block_size)
{
	const char	*sp = "!@#$ %^&*()-+={}[]\\|;'\"<>,?~";
	int			i;

	i = 0;
	if (block_size <= 0 || word[i] != '$')
		return (0);
	if (word[1] == '?')
		return (2);
	while (++i < block_size)
	{
		if (ft_strchr(sp, word[i]))
			break ;
	}
	return (i);
}

char	*change_envvalue(char *word, int start, int size, t_arg *arg)
{
	char	*change_word;
	char	*value;

	if (word[start + 1] == '?')
	{
		value = ft_itoa(arg->stat_loc);
		if (!value)
			return (NULL);
	}
	else
		value = get_value_env(word + start + 1, size - 1, arg->env);
	if (!value)
		value = "";
	change_word = ft_strchange(word, start, start + size, value);
	if (!change_word)
		return (NULL);
	if (word[start + 1] == '?')
		free(value);
	return (change_word);
}

int	_change_block_env(char **word, int i, t_blockinfo *bi, t_arg *arg)
{
	char	*change_word;
	int		ch_word_size;
	int		env_size;

	env_size = get_env_size(*word + i, bi->end - i);
	if (env_size > 1)
	{
		change_word = change_envvalue(*word, i, env_size, arg);
		if (!change_word)
			return (1);
		ch_word_size = ft_strlen(change_word);
		free(*word);
		*word = change_word;
		bi->end += ch_word_size - bi->word_size;
		bi->word_size = ch_word_size;
	}
	return (0);
}

int	change_block_env(char **word, t_blockinfo *bi, t_arg *arg)
{
	int	i;

	if (bi->quotes == '\'')
		return (0);
	i = bi->start;
	while (i < bi->end)
	{
		if ((*word)[i] == '$')
		{
			if (_change_block_env(word, i, bi, arg))
				return (1);
		}
		i++;
	}
	return (0);
}
