/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:36:41 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/24 15:38:55 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_status(t_mini *m, int *status)
{
	if (*status == 0)
	{
		m->exit_status = m->exit_status >> 8;
		*status = m->exit_status;
		printf("%d", m->exit_status);
	}
	else
		printf("%d", (*status));
}
void	loop_echo(t_mini *m, char **cmd, int i, int j)
{
	int	status;

	status = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "$?", 3) == 0)
			handle_status(m, &status);
		else
		{
			while (cmd[i][j] != '\0')
			{
				if (cmd[i][j] == '\\')
					j++;
				write(1, &cmd[i][j], 1);
				j++;
			}
		}
		j = 0;
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

void	ft_echo(t_mini *m, char **cmd)
{
	int		i;
	int		j;
	bool	n_flag;

	j = 0;
	n_flag = false;
	/* if (cmd[1] == NULL)
	{
		printf("\n");
		error_handle(m, "", "", 27);
		return ;
	} */
	if (ft_strcmp(cmd[1], "-n") == 0)
	{
		i = 2;
		n_flag = true;
	}
	else
		i = 1;
	loop_echo(m, cmd, i, j);
	if (n_flag == false)
		printf("\n");
	error_handle(m, "", "", 0);
}
