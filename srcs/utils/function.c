/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:17:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/27 16:47:09 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_double_char_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	cp_env(char **env, char **env_cp)
{
	int	i;

	i = 0;
	while (env[i])
	{
		env_cp[i] = ft_strdup(env[i]);
		i++;
	}
	env_cp[i] = NULL;
}

int	ft_strlen_arg(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

void	j_handle_target(char **envp, int i, int *j, char *target)
{
	char	max;

	max = ft_strlen(target);
	while (envp[i][*j] && envp[i][*j] != '=')
		(*j)++;
	if ((*j > max))
		max = *j;
}

char	*target_path(t_mini *m, char **envp, char *target, int status)
{
	int		i;
	char	*path;
	int		j;
	int		max;

	j = 0;
	i = 0;
	while (envp[i])
	{
		max = ft_strlen(target);
		j_handle_target(envp, i, &j, target);
		if (ft_strncmp(envp[i], target, max) == 0)
		{
			path = ft_substr(envp[i], ft_strlen(target), ft_strlen(envp[i]));
			m->path_count = i;
			if (status == 1)
				return (path);
			free(path);
			return ("ok");
		}
		j = 0;
		i++;
	}
	return (NULL);
}
