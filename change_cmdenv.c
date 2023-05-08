/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cmdenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:00:29 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/08 20:42:21 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env(char *key, char **env)
{
	char	*value;
	int		i;
	int		idx;

	value = NULL;
	i = -1;
	while (env[++i])
	{
		idx = ft_strlen(key);
		if (!ft_strncmp(key, env[i], idx) && env[i][idx] == '=')
		{
			value = env[i] + idx + 1;
			break ;
		}
	}
	return (value);
}

int	set_word_change(char *word, int idx, char **env)
{
	char	*value;
	char	*new_word;

	value = get_value_env(word + idx + 1, env);
	if (value)
	{
		value = ft_strdup("");
		if (!value)
			return (1);
	}
	new_word = ft_strsizejoin(word, idx, value);
	if (!new_word)
		return (1);
	free(word);
	word = new_word;
	return (0);
}

int	change_env_list(char **list, char **env)
{
	int	i;
	int	idx;

	i = -1;
	while (list[++i])
	{
		idx = is_in_idx(list[i], "$");
		if (idx != -1)
		{
			if (set_word_change(list[i], idx, env))
				return (1);
		}
	}
	return (0);
}

int	change_allist_env(t_cmds *cmds, t_arg *arg)
{
	t_cmds	*now;

	now = cmds;
	while (now)
	{
		if (change_env_list(now->cmd, arg->env))
			return (print_perror("PARSE ERROR"));
		if (change_env_list(now->file, arg->env))
			return (print_perror("PARSE ERROR"));
		now = now->next;
	}
	return (0);
}
