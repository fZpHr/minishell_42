/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:01:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/17 16:43:25 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_status(int status)
{
	if (status == 0)
		exit(0);
	else if (status == 1)
		exit(1);
	else if (status == 2)
		exit(2);
	else if (status == 126)
		exit(126);
	else if (status == 127)
		exit(127);
}

void	free_split(t_mini *m)
{
	int	i;

	i = 0;
	if (m->cmd)
	{
		while (m->cmd[i])
		{
			free(m->cmd[i]);
			i++;
		}
		free(m->cmd[i]);
		free(m->cmd);
	}
}

void	free_end(t_mini *m, int status)
{
	free_split(m);
	if (m->input)
		free(m->input);
	error_status(status);
}
