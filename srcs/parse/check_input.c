/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:56:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/07 17:00:38 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cut_useless(t_mini *m)
{
	while (m->cmd[m->intern_last--] != 0)
	{
		free(m->cmd[m->intern_last]);
		m->cmd[m->intern_last] = NULL;
	}
}

int		build_intern(char *c)
{
	if (ft_strcmp(c, "echo") == 0)
		return (1);
	else if (ft_strcmp(c, "cd") == 0)
		return (1);
	else if (ft_strcmp(c, "pwd") == 0)
		return (1);
	else if (ft_strcmp(c, "export") == 0)
		return (1);
	else if (ft_strcmp(c, "unset") == 0)
		return (1);
	else if (ft_strcmp(c, "env") == 0)
		return (1);
	else if (ft_strcmp(c, "exit") == 0)
		return (1);
	return (0);
}

void	check_input(t_mini *m)
{
	int i;
	i = 0;
	while (m->cmd[i])
	{
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
	ft_cut_useless(m);
}
