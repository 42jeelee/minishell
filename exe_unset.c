/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:56:14 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/27 16:55:57 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static int	is_invalid_identifier_in_str(const char *str);
static void	exe_unset_del_one(char *str, char **env);

int	exe_unset(char **cmd, char **env)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	if (cmd[1] == 0)
		return (0);
	i = 0;
	while (cmd[++i])
	{
		if (is_invalid_identifier_in_str(cmd[i]))
		{
			write(2, "unset: `", 9);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			exit_code = 1;
		}
		else if (find_str_idx_in_env(cmd[i], env) == -1)
			continue ;
		else
			exe_unset_del_one(cmd[i], env);
	}
	return (exit_code);
}

static void	exe_unset_del_one(char *str, char **env)
{
	int		i;
	int		env_size;
	int		del_idx;

	i = 0;
	env_size = 0;
	while (env[env_size])
		env_size++;
	del_idx = find_str_idx_in_env(str, env);
	free(env[del_idx]);
	env[del_idx] = 0;
	while (i < env_size)
	{
		if (env[i] == 0)
		{
			env[i] = env[i + 1];
			env[i + 1] = 0;
		}
		i++;
	}
}

static int	is_invalid_identifier_in_str(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'
			&& str[i] != '=')
			return (1);
		i++;
	}
	return (0);
}
