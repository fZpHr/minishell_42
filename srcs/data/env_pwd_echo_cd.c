/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd_echo_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:51:19 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/14 17:00:59 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_mini *m)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		error_handle(m, "error", "", 1);
		return ;
	}
	printf("%s\n", pwd);
	error_handle(m, "", "", 0);
}

void	ft_env(t_mini *m, char **env, int status)
{
	int		i;
	
	if (m->alloc_env == 1)
	{
		i = 0;
		if (status == 1)
			while (m->envm[i])
				printf("%s\n", m->envm[i++]);
	}
	else
	{
		m->alloc_env = 1;
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
	error_handle(m, "", "", 0);
}

void	ft_echo(t_mini *m, char **cmd)
{
	int		i;
	
	if (cmd[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(cmd[1], "-n") == 0)
	{
		i = 2;
		while (cmd[i])
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			i++;
		}
	}
	else if (ft_strchr(cmd[1], 36) != 0)
	{
		i = 1;
		if (ft_strncmp(cmd[1], "$?", 3) == 0)
			printf("%d\n", m->exit_status);
		else
		{
			while (cmd[i])
			{
				if (target_path(m->envm, cmd[i] + 1) != NULL)
					printf("%s\n", target_path(m->envm, cmd[i] + 1));
				else
					printf("\n");
				i++;
			}
		}
	}
	else
	{
		i = 1;
		while (cmd[i])
			printf("%s\n", cmd[i++]);
	}
	error_handle(m, "", "", 0);
}

void	ft_cd(t_mini *m, char **cmd)
{
	char	*home;

	if (!m->old_pwd_cd)
		m->old_pwd_cd = getcwd(NULL, 0);
	m->pwd_cd = getcwd(NULL, 0);
	if (cmd[1] == NULL)
	{
		home = target_path(m->envm, "HOME=");
		if (home == NULL)
		{
			error_handle(m, "env error", "", 1);
			return ;
		}
		else
		{
			if (chdir(home) == -1)
			{
				error_handle(m, "chdir error", "", 1);
				return ;
			}
		}
		free(home);
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		home = m->old_pwd_cd;
		if (home == NULL)
		{
			error_handle(m, "env error", "", 1);
			return ;
		}
		else
		{
			if (chdir(home) == -1)
			{
				error_handle(m, "chdir error", "", 1);
				return ;
			}
			else
				printf("%s\n", home);
		}
		free(home);
	}
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			error_handle(m, "cd : no such file or directory:", cmd[1], 1);
			return ;
		}
	}
	m->old_pwd_cd = m->pwd_cd;
	error_handle(m, "", "", 0);
}
