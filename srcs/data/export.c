/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:05:30 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 15:10:16 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printf_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}

void	loop_sort_ascii(char **env_cp, int *j, char **tmp)
{
	int	i;

	i = 0;
	while (env_cp[i])
	{
		*j = i + 1;
		while (env_cp[*j])
		{
			if (ft_strcmp(env_cp[i], env_cp[*j]) > 0)
			{
				*tmp = env_cp[i];
				env_cp[i] = env_cp[*j];
				env_cp[*j] = *tmp;
			}
			(*j)++;
		}
		i++;
	}
}

void	sort_ascii(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	**env_cp;

	env_cp = (char **)malloc(sizeof(char *) * (ft_double_char_len(env) + 1));
	cp_env(env, env_cp);
	i = 0;
	loop_sort_ascii(env_cp, &j, &tmp);
	while (env_cp[i])
	{
		tmp = ft_strjoin("declare -x ", env_cp[i]);
		free(env_cp[i]);
		env_cp[i] = tmp;
		i++;
	}
	printf_env(env_cp);
	free_split(env_cp);
}

void	loop_export(t_mini *m, int *i)
{
	char	*tmp;
	int		l;

	l = 1;
	while (m->cmd[l] != NULL)
	{
		tmp = cut_cmd_char(m, m->cmd[l]);
		if (target_path(m, m->envm, tmp, 0) != NULL)
		{
			free(m->envm[m->path_count]);
			m->envm[m->path_count] = ft_strdup(m->cmd[l]);
			m->path_count = 0;
		}
		else
		{
			m->envm[*i] = ft_strdup(m->cmd[l]);
			(*i)++;
		}
		free(tmp);
		l++;
	}
}

void	ft_export(t_mini *m, char **env)
{
	int		i;
	int		l;
	char	**tmp;

	ft_env(m, env, 0);
	i = ft_double_char_len(env);
	if (m->cmd[1] == NULL)
	{
		ft_env(m, m->envm, 0);
		sort_ascii(m->envm);
	}
	else
	{
		l = ft_double_char_len(m->cmd);
		tmp = (char **)malloc(sizeof(char *) * (i + l));
		cp_env(m->envm, tmp);
		free_split(m->envm);
		m->envm = tmp;
		add_null(m->envm, i, l);
		loop_export(m, &i);
	}
	if (m->status_exit == 1)
		error_handle(m, "export", "not a valid identifier", 1);
	else
		error_handle(m, "", "", 0);
}
