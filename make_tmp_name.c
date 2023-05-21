/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tmp_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:19:06 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 19:25:39 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

static char	**free_all(char **tmp_name, int last_idx);

char	**make_tmp_name(t_cmds *cmds)
{
	char	**tmp_name;
	int		cmds_len;
	char	*itoa_word;
	int		i;

	cmds_len = ft_cmdssize(cmds);
	i = 0;
	tmp_name = malloc(sizeof(char *) * (cmds_len + 1));
	if (tmp_name == 0)
		return (0);
	while (i < cmds_len)
	{
		itoa_word = ft_itoa(i);
		if (itoa_word == 0)
			return (free_all(tmp_name, i));
		tmp_name[i] = ft_strjoin(".heredoctmpfile", itoa_word);
		if (tmp_name[i] == 0)
			return (free_all(tmp_name, i + 1));
		free(itoa_word);
		i++;
	}
	tmp_name[i] = 0;
	return (tmp_name);
}

static char	**free_all(char **tmp_name, int last_idx)
{
	int	i;

	i = 0;
	while (i < last_idx)
		free(tmp_name[i++]);
	free(tmp_name);
	return (0);
}
