/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:31:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/24 17:53:57 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	infinite_loop(int fd[2], char *end, t_mini *m)
{
	char	*input;

	(void)m;
	while (1)
	{
		input = readline("heredoc> ");
		if (signal_flag[2] == 1 || ft_strncmp(input, end, ft_strlen(end)) == 0)
		{
			free(input);
			free_split(m->cmd);
			ft_listclear(&m->head, free);
			free_split(m->envm);
			exit(0);
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
}

void	here_doc(t_mini *m, char *end)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error_handle(m, "pipex: error pipe", "", 1);
	pid = fork();
	if (pid == -1)
		error_handle(m, "pipex: error fork", "", 1);
	if (pid == 0)
		infinite_loop(fd, end, m);
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	if (m->status_child == 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
}
