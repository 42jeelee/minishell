/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:56:41 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/28 01:25:24 by jeelee           ###   ########.fr       */
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
	int		i;
	char	c;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		c = str[i];
		while (str[++i])
		{
			if (str[i] == c)
				return (i);
		}
	}
	return (0);
}

int	get_block_size(char *word, char c)
{
	int	start;
	int	end;
	int	size;

	start = 0;
	while (word[start])
	{
		end = str_in_idx(word + start, "\"\'");
		if (end != -1)
		{
			if (c == word[start + end])
				return (start + end);
			if (!c)
			{
				size = quotes_blockidx(word + start + end);
				if (size > 0)
					return (start + end);
			}
			start += end + 1;
		}
		else
			break ;
	}
	return (ft_strlen(word));
}

int	find_key_env(char *key, char **env)
{
	int	i;
	int	key_size;

	if (!key | !(key[0]))
		return (-1);
	key_size = ft_strlen(key);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(key, env[i], key_size + 1) || \
			(!ft_strncmp(key, env[i], key_size) && (env[i])[key_size] == '='))
			return (i);
	}
	return (-1);
}

int	set_g_pwd(t_arg *arg)
{
	char	*tmp;

	tmp = ft_getpwd(arg->env);
	if (!tmp)
		return (1);
	if (arg->pwd)
		free(arg->pwd);
	arg->pwd = tmp;
	return (0);
}
