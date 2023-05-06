/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeelee <jeelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:38:43 by jeelee            #+#    #+#             */
/*   Updated: 2023/05/06 00:06:14 by jeelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "new_prompt.h"
# include "exe_cmd_line.h"

// PRINT
void	print_cmds(t_arg *arg, t_cmds *cmds);
void	print_arg(t_arg *arg);

#endif
