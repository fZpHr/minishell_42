/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:36:39 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/01 19:30:09 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init(t_mini *m)
{
	m->cmd = NULL;
	m->input = NULL;
	m->env_md = 0;
}

void	init_p(t_pipex *p)
{
	p->cmd1 = NULL;
	p->cmd2 = NULL;
	p->envp = NULL;
	p->tmp = NULL;
	p->ac = 0;
	p->tmp_end = NULL;
	p->tmp_child = NULL;
}
