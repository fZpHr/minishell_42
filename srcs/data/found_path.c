/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:07:23 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/23 19:36:18 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*found_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	free_path_split(char **path_split, char *path)
{
	int	i;

	i = 0;
	if (path)
		free(path);
	if (path_split)
	{
		while (path_split[i])
			free(path_split[i++]);
		free(path_split);
	}
}

char	*check_null(char **path_split, char *path, char *cmd)
{
	if (!path_split || !path || !cmd)
	{
		free_path_split(path_split, path);
		return (NULL);
	}
	return (cmd);
}

char	*loop_found_cmd(char **path_split, char *path, char *cmd)
{
	char	*cmd_path_tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	if (!check_null(path_split, path, cmd))
		return (NULL);
	while (path_split[i])
	{
		cmd_path_tmp = ft_strjoin(path_split[i], "/");
		cmd_path = ft_strjoin(cmd_path_tmp, cmd);
		free(cmd_path_tmp);
		if (access(cmd_path, F_OK) == 0)
		{
			free_path_split(path_split, path);
			return (cmd_path);
		}
		else
			free(cmd_path);
		i++;
	}
	free_path_split(path_split, path);
	return (NULL);
}

char	*found_cmd(t_mini *m, char **envp)
{
	char	*path;
	char	**path_split;
	char	*res;

	path = found_path(envp);
	if (!path)
		return (NULL);
	path_split = ft_split(path, ":");
	if (!path_split)
		return (NULL);
	res = loop_found_cmd(path_split, path, m->cmd[0]);
	if (res)
		return (res);
	return (NULL);
}
