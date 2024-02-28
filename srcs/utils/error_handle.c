/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:58:56 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/28 17:23:00 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	status_handle(t_mini *m, int *status, char *target, char *str)
{
	if (*status > 0)
	{
		if (ft_strncmp(m->cmd[0], "exit", 5) == 0)
		{
			if (m->cmd[1])
			{
				if (m->cmd[2])
				{
					ft_printf_error("exit\nexit : too many arguments\n");
					*status = *status - 1000;
					m->exit_status = 1;
				}
			}
		}
		else if (ft_strncmp(target, "$?", 3) == 0)
			ft_printf_error("%s %d\n", str, m->exit_status);
		else
			ft_printf_error("%s %s\n", str, target);
	}
}

void	monitor_status(t_mini *m, int *status, char *target, char *str)
{
	if (*status >= 1000 && *status < 1500)
		m->exit_status = *status - 1000;
	else if (*status >= 1500)
		m->exit_status = (*status - 1000) >> 8;
	else if (*status < 1000 && *status >= 150)
	{
		m->exit_status = *status - 1000;
		*status = *status + 1000;
	}
	else
		m->exit_status = *status;
	if (*status > 0)
		status_handle(m, status, target, str);
	ft_putstr_fd("\033[0m", 2);
	if (*status >= 1000)
		free_end(m, m->exit_status);
}

void	ctrl_d_handle(t_mini *m)
{
	free_split(m->envm);
	close(m->savefd[0]);
	close(m->savefd[1]);
	exit(m->exit_status >> 8);
}

void	error_handle(t_mini *m, char *str, char *target, int status)
{
	ft_putstr_fd("\033[0;31m", 2);
	if (status == 9001)
	{
		ft_putstr_fd("\033[0m", 2);
		ctrl_d_handle(m);
	}
	if (status >= 0)
		monitor_status(m, &status, target, str);
	else
	{
		ft_putstr_fd("\033[0m", 2);
		m->exit_status = m->exit_status >> 8;
		free_end(m, m->exit_status);
	}
}
