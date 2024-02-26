/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:44:55 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 15:20:42 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_flag(t_mini *m, char **home)
{
	(*home) = m->old_pwd_cd;
	if ((*home) == NULL)
	{
		error_handle(m, "env error", "", 1);
		return (1);
	}
	else
	{
		if (chdir((*home)) == -1)
		{
			error_handle(m, "chdir error", "", 1);
			return (1);
		}
		else
			printf("%s\n", (*home));
	}
	//free((*home));
	return (0);
}

int	cd_null(t_mini *m, char **home)
{
	(*home) = target_path(m, m->envm, "HOME=", 1);
	if ((*home) == NULL)
	{
		error_handle(m, "env error", "", 1);
		return (1);
	}
	else
	{
		if (chdir((*home)) == -1)
		{
			error_handle(m, "chdir error", "", 1);
			return (1);
		}
	}
	free((*home));
	return (0);
}

void	ft_cd(t_mini *m, char **cmd)
{
	char	*home;

	if (!m->old_pwd_cd)
		m->old_pwd_cd = getcwd(NULL, 0);
	m->pwd_cd = getcwd(NULL, 0);
	if (cmd[1] == NULL)
	{
		if (cd_null(m, &home) == 1)
			return ;
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		if (cd_flag(m, &home) == 1)
			return ;
	}
	else
	{
		if (chdir(cmd[1]) == -1)
			return (error_handle(m, "cd : no such file or directory:", cmd[1],
					1));
	}
	free(m->old_pwd_cd);
	m->old_pwd_cd = m->pwd_cd;
	error_handle(m, "", "", 0);
}
