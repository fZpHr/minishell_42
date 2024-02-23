/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:24:54 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/23 19:51:24 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	do_redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	do_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
