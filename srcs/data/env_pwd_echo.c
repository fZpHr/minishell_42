/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:51:19 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/01 19:33:13 by hbelle           ###   ########.fr       */
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
		if (status == 2)
			while (m->envm[i])
				printf("%s\n", m->envm[i++]);
	}
}

void  sort_ascii(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	**env_cp;

	env_cp = (char **)malloc(sizeof(char *) * (ft_double_char_len(env) + 1));
	cp_env(env, env_cp);
	i = 0;
	while (env_cp[i])
	{
		j = i + 1;
		while (env_cp[j])
		{
			if (ft_strcmp(env_cp[i], env_cp[j]) > 0)
			{
				tmp = env_cp[i];
				env_cp[i] = env_cp[j];
				env_cp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env_cp[i])
		printf("%s\n", env_cp[i++]);
}


void	ft_export(t_mini *m, char **env)
{
	int		i;

	ft_env(m, env, 0);
	i = ft_double_char_len(env);
	if (m->cmd[1] == NULL)
	{
		ft_env(m, m->envm, 0);
		sort_ascii(m->envm);
	}
	else
	{
		char **tmp = (char **)malloc(sizeof(char *) * (i + 2));
		i = 0; 
		while (m->envm[i])
		{
			tmp[i] = ft_strdup(m->envm[i]);
			i++;
		}
		free_split(m->envm);
		m->envm = tmp;
		if (m->cmd[2] == NULL)
		{
			if (ft_strchr(m->cmd[1], '=') == NULL)
				return ;
			m->envm[i] = ft_strdup(m->cmd[1]);
			m->envm[i + 1] = NULL;
		}
		else
		{
			if (ft_strchr(m->cmd[1], '=') == NULL)
				return ;
			m->envm[i] = ft_strdup(m->cmd[1]);
			m->envm[i + 1] = NULL;
		}
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
