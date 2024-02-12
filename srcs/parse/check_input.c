/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:56:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/12 16:37:28 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	ft_cut_useless(t_mini *m)
{
	ft_memmove(&m->cmd[0], &m->cmd[m->intern_last], (m->count_cmd - m->intern_last) * sizeof(m->cmd[0]));
	ft_memset(&m->cmd[m->count_cmd - m->intern_last], 0, m->intern_last * sizeof(m->cmd[0]));
}*/

int		build_intern(t_mini *m, char *c)
{
	char **tmp;

	tmp = ft_split(c, " ");
	if (ft_strcmp(tmp[0], "echo") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "cd") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "pwd") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "env") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "export") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "unset") == 0)
	{
		free_split(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp[0], "exit") == 0)
	{
		free_split(tmp);
		error_handle(m, "", "", 1000);
	}
	return (0);
}

/*void	check_input(t_mini *m)
{
	int i;
	i = 0;
	while (m->cmd[i])
	{
		m->count_cmd++;
		if (ft_strcmp(m->cmd[i], ">>") == 0)
			m->append_right = i;
		else if (ft_strcmp(m->cmd[i], "<<") == 0)
			m->append_left = i;
		else if (ft_strcmp(m->cmd[i], ">") == 0)
			m->redi_right = i;
		else if (ft_strcmp(m->cmd[i], "<") == 0)
			m->redi_left = i;
		else if (build_intern(m->cmd[i]) == 1)
			m->intern_last = i;
		i++;
	}
	if (i > 1 && m->intern_last > 0)
		ft_cut_useless(m);
}*/
