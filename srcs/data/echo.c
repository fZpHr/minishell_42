/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:17:17 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/06 16:17:17 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	loop_echo(t_mini *m, char **cmd, int i, int j)
{
	int	status;

	status = 0;
	while (cmd[i])
	{
		if (status == 1)
			write(1, " ", 1);
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '\\')
				j++;
			write(1, &cmd[i][j], 1);
			if (cmd[i][j] != '\0')
				j++;
		}
		j = 0;
		if (cmd[i + 1] != NULL && m->status_redir_out == 0
			&& m->status_append == 0)
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
