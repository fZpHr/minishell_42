/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:24:54 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/29 16:36:29 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_redir_in(t_mini *m, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		m->error_open = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	do_redir_out(t_mini *m, char *file)
{
	int	fd;

	if (access(file, F_OK) == 0)
		fd = open(file, O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		error_handle(m, "", "", 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	do_append(t_mini *m, char *file)
{
	int	fd;

	if (access(file, F_OK) == 0)
		fd = open(file, O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		error_handle(m, "", "", 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
