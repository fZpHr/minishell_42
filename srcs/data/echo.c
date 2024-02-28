/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:36:41 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/28 17:27:34 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	loop_echo(char **cmd, int i, int j)
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
			j++;
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
	if (ft_strcmp(cmd[1], "-n") == 0)
	{
		i = 2;
		n_flag = true;
	}
	else
		i = 1;
	loop_echo(cmd, i, j);
	if (n_flag == false)
		printf("\n");
	error_handle(m, "", "", 0);
}
