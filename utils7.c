/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:44:21 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/27 18:30:54 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error_msg(char *word)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(word, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

int	is_empty_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			return (0);
	}
	return (1);
}

int	is_syntax_error2(int type, char *word, char *next_command)
{
	int		word_type;
	char	*next_word;

	next_word = NULL;
	if (type && !word)
	{
		word_type = is_redirection(next_command);
		if (word_type == 0)
			next_word = "newline";
		else if (word_type == INONE)
			next_word = "<";
		else if (word_type == INTWO)
			next_word = "<<";
		else if (word_type == OUTONE)
			next_word = ">";
		else if (word_type == OUTTWO)
			next_word = ">>";
		syntax_error_msg(next_word);
		return (1);
	}
	return (0);
}

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
