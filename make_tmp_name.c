/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tmp_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byejeon <byejeon@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:19:06 by byejeon           #+#    #+#             */
/*   Updated: 2023/05/21 14:19:49 by byejeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd_line.h"

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
		exit(print_perror("tmp_file"));
	while (i < cmds_len)
	{
		itoa_word = ft_itoa(i);
		tmp_name[i] = ft_strjoin(".heredoctmpfile", itoa_word);
		free(itoa_word);
		i++;
	}
	tmp_name[i] = 0;
	return (tmp_name);
}
