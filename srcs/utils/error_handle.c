/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:58:56 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/24 17:10:11 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_handle(t_mini *m, char *str, char *target, int status)
{
	ft_putstr_fd("\033[0;31m", 2);
	if (status == 9999)
		m->exit_fork = 1;
	if (status >= 1000)
	{
		m->exit_status = status - 1000;
		if (m && m->head)
			ft_listclear(&m->head, free);
	}
	else if (status == 27)
	{
		if (m && m->head)
			ft_listclear(&m->head, free);
		free_split(m->cmd);
	}
	else
		m->exit_status = status << 8;
	if (status > 0)
		printf("%s %s\n", str, target);
	ft_putstr_fd("\033[0m", 2);
	if (status == 127)
		free_end(m, m->exit_status);
	if (status >= 1000)
		free_end(m, m->exit_status);
}
