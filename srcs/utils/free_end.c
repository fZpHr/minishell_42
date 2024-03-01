/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:01:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/28 15:43:01 by hbelle           ###   ########.fr       */
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

void	handle_free(t_mini *m)
{
	if (m->head)
		ft_listclear(&m->head, free);
	if (m->alloc_env == 1)
		free_split(m->envm);
	if (m->cmd)
		free_split(m->cmd);
	if (m->input)
		free(m->input);
	if (m->pwd_cd)
		free(m->pwd_cd);
}

int	check_exist(t_mini *m)
{
	int	j;

	j = 0;
	if (ft_strncmp(m->cmd[0], "exit", 5) == 0)
	{
		while (m->cmd[1] && m->cmd[1][j])
		{
			if ((m->cmd[1][j] == '-' && j == 0) || (m->cmd[1][j] == '+'
					&& j == 0))
				j++;
			if (ft_isdigit(m->cmd[1][j]) == 0)
			{
				ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
				m->exit_status = 2;
				return (1);
			}
			j++;
		}
	}
	return (0);
}

void	free_end(t_mini *m, int status)
{
	int	i;

	i = 3;
	if (check_exist(m) == 1)
		return ;
	if (status > 255)
		status = status % 256;
	close(m->savefd[0]);
	close(m->savefd[1]);
	while (i <= 1023)
		close(i++);
	handle_free(m);
	exit(status);
}
