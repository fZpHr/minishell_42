/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:06:14 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/27 18:20:01 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_mini *m)
{
	close(m->savefd[0]);
	close(m->savefd[1]);
	close(m->fd[0]);
	close(m->fd[1]);
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
	tmp = (char *)ft_malloc(sizeof(char) * (l + 1));
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

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error: ft_malloc failed\n", 2);
		exit(1);
	}
	return (ptr);
}

void	handle_exec(t_mini *m, char *path)
{
	free(path);
	error_handle(m, "error execve", m->cmd[0], 1126);
}
