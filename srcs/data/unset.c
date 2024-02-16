/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:10:17 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/16 15:50:14 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_mini *m)
{
	int		i;
	int		j;
	char	**env_cp;

	i = 0;
	j = 0;
	env_cp = (char **)malloc(sizeof(char *) * (ft_double_char_len(m->envm) + 1));
	while (m->envm[i])
	{
		if (ft_strncmp(m->envm[i], m->cmd[1], ft_strlen(m->cmd[1])) != 0)
		{
			env_cp[j] = ft_strdup(m->envm[i]);
			j++;
		}
		i++;
	}
	env_cp[j] = NULL;
	free_split(&m->envm);
	m->envm = env_cp;
}
