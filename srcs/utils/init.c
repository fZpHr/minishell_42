/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:18:55 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/06 16:18:55 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_char(t_mini *m)
{
	m->input = NULL;
	m->cmd = NULL;
	m->heredoc_delimiter = NULL;
	m->old_pwd_cd = NULL;
	m->pwd_cd = NULL;
	m->envm = NULL;
	m->path = NULL;
	m->head = NULL;
	m->tmp_end = NULL;
	m->tmp_child = NULL;
}

void	init(t_mini *m)
{
	init_char(m);
	m->heredoc_status = 0;
	m->parse = 0;
	m->parse_error = 0;
	m->status_redir_out = 0;
	m->error_open = 0;
	m->status_exit = 0;
	m->savefd[0] = 0;
	m->savefd[1] = 0;
	m->alloc_env = 0;
	m->ac = 0;
	m->exit_status = 0;
	m->status_append = 0;
	m->parse_error = 0;
	m->max_unset = 0;
	g_signal_flag[0] = 0;
	g_signal_flag[1] = 0;
	g_signal_flag[2] = 0;
	g_signal_flag[3] = 0;
}
