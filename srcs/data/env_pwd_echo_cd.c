/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd_echo_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:51:19 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/05 15:02:25 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_mini *m)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		error_handle(m, "error\n", "", 1);
	printf("%s\n", pwd);
	free(pwd);
}

void	ft_env(t_mini *m, char **env, int status)
{
	int		i;
	
	if (m->env_md == 1)
	{
		i = 0;
		if (status == 1)
			while (m->envm[i])
				printf("%s\n", m->envm[i++]);
	}
	else
	{
		m->env_md = 1;
		i = 0;
		m->envm = (char **)malloc(sizeof(char *) * (ft_double_char_len(env) + 1));
		while (env[i])
		{
			m->envm[i] = ft_strdup(env[i]);
			i++;
		}
		m->envm[i] = NULL;
		i = 0;
		if (status == 1)
			while (m->envm[i])
				printf("%s\n", m->envm[i++]);
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
			printf("%s\n", m->cmd[i++]);
	}
}

int	ft_cd(t_mini *m)
{
	char	*home;

	if (!m->old_pwd_cd)
		m->old_pwd_cd = getcwd(NULL, 0);
	m->pwd_cd = getcwd(NULL, 0);
	if (m->cmd[1] == NULL)
	{
		home = target_path(m->envm, "HOME=");
		if (home == NULL)
			error_handle(m, "error ", "", 1);
		else
		{
			if (chdir(home) == -1)
				error_handle(m, "error ", "", 1);
		}
		free(home);
	}
	else if (ft_strcmp(m->cmd[1], "-") == 0)
	{
		home = m->old_pwd_cd;
		if (home == NULL)
			error_handle(m, "error ", "", 1);
		else
		{
			if (chdir(home) == -1)
				error_handle(m, "error ", "", 1);
			else
				printf("%s\n", home);
		}
		free(home);
	}
	else
	{
		if (chdir(m->cmd[1]) == -1)
		{
			printf("cd : no such file or directory: %s\n", m->cmd[1]);
			return (1);
		}
	}
	m->old_pwd_cd = m->pwd_cd;
	return (0);
}
