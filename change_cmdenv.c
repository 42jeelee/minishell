/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cmdenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:00:29 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/09 01:53:31 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env(char *key, int *end, char **env)
{
	char	*value;
	int		i;

	value = NULL;
	*end = is_in_idx(key, "$");
	if (*end == -1)
		*end = ft_strlen(key);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(key, env[i], *end) && env[i][*end] == '=')
		{
			value = env[i] + *end + 1;
			break ;
		}
	}
	return (value);
}

int	set_word_change(char **word, int idx, char **env)
{
	char	*value;
	char	*new_word;
	int		end;

	value = get_value_env(*word + idx + 1, &end, env);
	if (!value)
		value = "";
	new_word = ft_strchange(*word, idx, end + idx + 1, value);
	if (!new_word)
		return (1);
	free(*word);
	*word = new_word;
	return (0);
}

int	change_env_list(char **list, char **env)
{
	int	i;
	int	idx;

	i = 0;
	while (list[i])
	{
		idx = is_in_idx(list[i], "$");
		if (idx != -1)
		{
			if (set_word_change(&(list[i]), idx, env))
				return (1);
		}
		else
			i++;
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
