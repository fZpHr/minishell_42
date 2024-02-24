/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:01:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/24 16:46:12 by tmekhzou         ###   ########.fr       */
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

void	free_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i])
		{
			//printf("freeing %s\n", cmd[i]);
			free(cmd[i]);
			cmd[i] = NULL;
		}
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void	free_end(t_mini *m, int status)
{
	if (m->head)
		ft_listclear(&m->head, free);
	if (m->alloc_env == 1)
		free_split(m->envm);
	if (m->alloc_cmd1 == 1)
		free_split(m->cmd1);
	if (m->cmd)
		free_split(m->cmd);
	if (m->input)
		free(m->input);
	if (m->tmp)
		free(m->tmp);
	error_status(status);
}
