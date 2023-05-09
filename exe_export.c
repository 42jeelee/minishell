#include "exe_cmd_line.h"

static void	exe_export_with_no_arg(char **env);
static int	is_invalid_identifier_in_str(const char *str);
void	exe_export_add_one(char *str, char ***env);
int		str_size_until_equal_or_null(const char *str);
int		find_str_idx_in_env(char *str, char **env);

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

void	exe_export_add_one(char *str, char ***env)
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

int	find_str_idx_in_env(char *str, char **env)
{
	int	i;
	int	size;

	i = 0;
	size = str_size_until_equal_or_null(str);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], size) == 0 &&
				(env[i][size] == '=' || env[i][size] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	str_size_until_equal_or_null(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static int	is_invalid_identifier_in_str(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || str[0] == '\0' || ft_isdigit(str[0]))
		return (1);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_' &&
				str[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

static void	exe_export_with_no_arg(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (env[i][j] && env[i][j] != '=')
			write(1, &env[i][j++], 1);
		if (env[i][j] == '=')
		{
			write(1, "=\"", 2);
			write(1, env[i] + j + 1, strlen(env[i] + j + 1));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

