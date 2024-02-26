/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:17:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 18:22:37 by tmekhzou         ###   ########.fr       */
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

char	*target_path(t_mini *m, char **envp, char *target, int status)
{
	int		i;
	char	*path;
	int		j;

	j = 0;
	i = 0;
	while (envp[i])
	{
		while (envp[i][j] != '=')
			j++;
		if (ft_strncmp(envp[i], target, j) == 0)
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

void	close_fds(t_mini *m)
{
	close(m->savefd[0]);
	close(m->savefd[1]);
	close(m->fd[0]);
	close(m->fd[1]);
}
