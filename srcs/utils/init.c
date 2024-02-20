/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:36:39 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/20 18:43:09 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init(t_mini *m)
{
	m->old_pwd_cd = NULL;
	m->pwd_cd = NULL;
	m->cmd = NULL;
	m->input = NULL;
	m->alloc_env = 0;
	m->cmd1 = NULL;
	m->cmd2 = NULL;
	m->envp = NULL;
	m->tmp = NULL;
	m->ac = 0;
	m->tmp_end = NULL;
	m->tmp_child = NULL;
	m->exit_status = 0;
	m->append_left = 0;
	m->append_right = 0;
	m->redi_left = 0;
	m->redi_right = 0;
	m->count_cmd = 0;
	m->intern_last = 0;
	m->alloc_cmd = 0;
	m->alloc_cmd1 = 0;
	m->alloc_path = 0;
	m->alloc_pwd = 0;
	m->status_append = 0;
	m->out = NULL;
	m->exec = 0;
	m->envm = NULL;
	m->env_path = NULL;
	m->path = NULL;
	m->status = 0;
	m->saved_stdin = 0;
	m->saved_stdout = 0;
	m->heredoc_status = 0;
	m->exit_fork = 0;
	m->end_status = 0;
	m->current_input = NULL;
	m->parse = 0;
	m->status_redir_out = 0;
	
}


