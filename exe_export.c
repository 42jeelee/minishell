/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:28:21 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/22 14:19:07 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static int	is_invalid_identifier_in_str(const char *str);
static int	exe_export_add_one(char *str, char ***env);

int	exe_export(char **cmd, char ***env)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (cmd[1] == 0)
		return (exe_export_with_no_arg(*env));
	while (cmd[i])
	{
		if (is_invalid_identifier_in_str(cmd[i]))
		{
			write(2, "export: `", 9);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			exit_code = 1;
		}
		else
			if (exe_export_add_one(cmd[i], env) > 0)
				return (1);
		i++;
	}
	return (exit_code);
}

static int	exe_export_add_one(char *str, char ***env)
{
	int		idx;
	char	*tmp;

	idx = find_str_idx_in_env(str, *env);
	if (idx >= 0)
	{
		if (ft_strchr(str, '='))
		{
			tmp = ft_strdup(str);
			if (tmp == 0)
				return (print_perror("export"));
			free((*env)[idx]);
			(*env)[idx] = tmp;
			return (0);
		}
	}
	else
		if (add_list_word(str, env) != 0)
			return (print_perror("export"));
	return (0);
}

static int	is_invalid_identifier_in_str(const char *str)
{
	int	i;
	int	end_idx;

	i = 0;
	if (str[0] == '=' || str[0] == '\0' || ft_isdigit(str[0]))
		return (1);
	end_idx = str_size_until_equal_or_null(str);
	while (i < end_idx)
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'
			&& str[i] != '=')
			return (1);
		i++;
	}
	return (0);
}
