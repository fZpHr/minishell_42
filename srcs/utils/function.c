/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:17:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/23 20:25:36 by hbelle           ###   ########.fr       */
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

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], target, ft_strlen(target)) == 0)
		{
			path = ft_substr(envp[i], ft_strlen(target), ft_strlen(envp[i]));
			m->path_count = i;
			if (status == 1)
				return (path);
			free(path);
			return ("ok");
		}
		i++;
	}
	return (NULL);
}

int	ft_count_cmd(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*cut_cmd_char(t_mini *m, char *cmd)
{
	char	*tmp;
	char	*find;
	char	l;

	find = ft_strchr(cmd, '=');
	if (!find)
	{
		if (ft_isalnum(cmd[0]) != 0)
			m->status_exit = 1;
		return (NULL);
	}
	l = ft_strlen_arg(cmd, '=') + 1;
	tmp = (char *)malloc(sizeof(char) * (l + 1));
	ft_strlcpy(tmp, cmd, l + 1);
	return (tmp);
}

void	add_null(char **env, int i, int l)
{
	while (l)
	{
		env[i] = NULL;
		i++;
		l--;
	}
}