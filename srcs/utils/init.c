/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:36:39 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/06 17:38:08 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init(t_mini *m)
{
	m->old_pwd_cd = NULL;
	m->pwd_cd = NULL;
	m->cmd = NULL;
	m->input = NULL;
	m->env_md = 0;
	m->cmd1 = NULL;
	m->cmd2 = NULL;
	m->envp = NULL;
	m->tmp = NULL;
	m->ac = 0;
	m->tmp_end = NULL;
	m->tmp_child = NULL;
	m->exit_status = 0;
}


