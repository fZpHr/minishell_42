/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stdin_stdout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:58:41 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/30 17:58:41 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stdin_stdout_handle(t_mini *m, int status)
{
    if (status == 0)
    {
		m->saved_stdin = dup(0);
   	    m->saved_stdout = dup(1);
    }
    else if (status == 1)
    {
		dup2(m->saved_stdin, 0);
  		dup2(m->saved_stdout, 1);
		close(m->saved_stdin);
   		close(m->saved_stdout);
    }
}