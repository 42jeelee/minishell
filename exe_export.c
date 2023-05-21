/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:28:21 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 21:26:41 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static void	exe_export_with_no_arg(char **env);
static int	is_invalid_identifier_in_str(const char *str);
static void	exe_export_add_one(char *str, char ***env);

void	exe_export(char **cmd, char ***env)
{
	int	i;

	i = 1;
	if (cmd[1] == 0)
		exe_export_with_no_arg(*env);
	while (cmd[i])
	{
		if (is_invalid_identifier_in_str(cmd[i]))
		{
			write(2, "export: `", 9);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		else
			exe_export_add_one(cmd[i], env);
		i++;
	}
}

static void	exe_export_add_one(char *str, char ***env)
{
	int	idx;

	idx = find_str_idx_in_env(str, *env);
	if (idx >= 0)
	{
		if (ft_strchr(str, '='))
		{
			free((*env)[idx]);
			(*env)[idx] = ft_strdup(str);
			if ((*env)[idx] == 0)
				exit(print_perror("export"));
			return ;
		}
	}
	else
		add_list_word(str, env);
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

static void	exe_export_with_no_arg(char **env)
{
	char	**copied_env;
	int		size;

	size = 0;
	while (env[size])
		size++;
	copied_env = malloc(sizeof(char *) * (size + 1));
	if (copied_env == 0)
		exit(print_perror("export"));
	copy_list(copied_env, env, size + 1);
	sort_export(copied_env);
	print_export(copied_env);
	free(copied_env);
}
