/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:51:19 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/30 19:51:19 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_mini *m)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		error_handle(m, "error\n", 1);
	printf("%s\n", pwd);
	free(pwd);
}

void	ft_env(char **env)
{
	int		i;
	
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	ft_echo(t_mini *m)
{
	int		i;

	if (m->cmd[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(m->cmd[1], "-n") == 0)
	{
		i = 2;
		while (m->cmd[i])
		{
			write(1, m->cmd[i], ft_strlen(m->cmd[i]));
			i++;
		}
	}
	else
	{
		i = 1;
		while (m->cmd[i])
			printf("%s ", m->cmd[i++]);
		printf("\nla");
	}
}
