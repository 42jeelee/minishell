/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cmdenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:00:29 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/11 17:11:10 by jeelee           ###   ########.fr       */
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
	int i;

	i = 0;
	if (block_size <= 0 || word[i] != '$')
		return (0);
	while (++i < block_size)
	{
		if (word[i] == '$' || word[i] == ' ')
			break ;
		else if (word[i] == '\'' || word[i] == '\"')
			break ;
	}
	return (i);
}

char	*change_envvalue(char *word, int start, int size, char **env)
{
	char	*change_word;
	char	*value;

	value = get_value_env(word + start + 1, size - 1, env);
	if (!value)
		value = "";
	change_word = ft_strchange(word, start, start + size, value);
	if (!change_word)
		return (NULL);
	return (change_word);
}

int	change_block_env(char **word, t_blockinfo *bi, char **env)
{
	char	*change_word;
	int		ch_word_size;
	int		env_size;
	int		i;

	while (1)
	{
		i = str_in_idx(*word, "$");
		if (i == -1 || bi->end <= i + 1)
			break ;
		env_size = get_env_size(*word + i, bi->end - i);
		change_word = change_envvalue(*word, i, env_size, env);
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
