/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/01/16 14:36:39 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/29 19:15:36 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	init(t_mini *m)
{
	m->envm = NULL;
	m->path = NULL;
	m->heredoc_status = 0;
	m->parse = 0;
	m->status_redir_out = 0;
	m->head = NULL;
	m->error_open = 0;
	m->status_exit = 0;
	m->savefd[0] = 0;
	m->savefd[1] = 0;
	m->old_pwd_cd = NULL;
	m->pwd_cd = NULL;
	m->cmd = NULL;
	m->input = NULL;
	m->alloc_env = 0;
	m->ac = 0;
	m->tmp_end = NULL;
	m->tmp_child = NULL;
	m->exit_status = 0;
	m->status_append = 0;
	m->parse_error = 0;
	m->max_unset = 0;
	m->heredoc_delimiter = NULL;
}
