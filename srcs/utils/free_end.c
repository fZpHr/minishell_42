/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:01:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 18:22:46 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i])
		{
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
	int	i;

	i = 3;
	close(m->savefd[0]);
	close(m->savefd[1]);
	while (i <= 1023)
		close(i++);
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
	if (m->pwd_cd)
		free(m->pwd_cd);
	exit(status);
}
