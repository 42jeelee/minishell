/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:23:48 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/24 19:23:14 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static char	*ft_getpwd_in_env(char **env);

char	*ft_getpwd(char **env)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (pwd == 0 && errno == 2)
		pwd = ft_getpwd_in_env(env);
	else if (pwd == 0)
		return (0);
	errno = 0;
	return (pwd);
}

static char	*ft_getpwd_in_env(char **env)
{
	char	*pwd;
	int		idx;

	idx = find_str_idx_in_env("PWD=", env);
	if (idx < 0)
		return (0);
	pwd = ft_strdup(env[idx] + 4);
	if (pwd == 0)
		return (0);
	return (pwd);
}
