/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:10:17 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 14:52:48 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_exist(t_mini *m, char **cmd)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	while (cmd[k])
	{
		while (m->envm[i])
		{
			if (ft_strncmp(m->envm[i], cmd[k], ft_strlen(cmd[k])) == 0)
				j++;
			i++;
		}
		i = 0;
		k++;
	}
	return (j);
}

void	loop_unset(t_mini *m, char ***env_cp, int *j)
{
	int	i;
	int	k;
	int	status;

	k = 1;
	i = 0;
	status = 0;
	while (m->cmd[k])
	{
		while (m->envm[i] && status == 0)
		{
			if (ft_strncmp(m->envm[i], m->cmd[k], ft_strlen(m->cmd[k])) != 0)
			{
				(*env_cp)[*j] = ft_strdup(m->envm[i]);
				(*j)++;
			}
			else
				status = 1;
			i++;
		}
		status = 0;
		k++;
	}
}

void	unset_if(t_mini *m, int l, int j)
{
	char	**env_cp;

	env_cp = (char **)malloc(sizeof(char *) * (ft_double_char_len(m->envm)
				+ l + 1));
	loop_unset(m, &env_cp, &j);
	env_cp[j] = NULL;
	free_split(m->envm);
	m->envm = env_cp;
}

void	ft_unset(t_mini *m)
{
	int		i;
	int		l;
	int		j;
	char	*save;

	i = 0;
	j = 0;
	while (m->cmd[i++])
	{
		if (m->cmd[i])
		{
			save = ft_strdup(m->cmd[i]);
			free(m->cmd[i]);
			m->cmd[i] = ft_strjoin(save, "=");
			free(save);
		}
	}
	l = check_if_exist(m, m->cmd);
	if (l > 0)
		unset_if(m, l, j);
	error_handle(m, "", "", 0);
}
