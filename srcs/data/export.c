/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:05:30 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/12 19:20:28 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void printf_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
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
	printf_env(env_cp);
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
			{
				error_handle(m, "export: ", m->cmd[2], 1);
				return ;
			}
			m->envm[i] = ft_strdup(m->cmd[1]);
			m->envm[i + 1] = NULL;
		}
		else
		{
			if (ft_strchr(m->cmd[1], '=') == NULL)
			{
				error_handle(m, "export: ", m->cmd[1], 1);
				return ;
			}
			m->envm[i] = ft_strdup(m->cmd[1]);
			m->envm[i + 1] = NULL;
		}
	}
}