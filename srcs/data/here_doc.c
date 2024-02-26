/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:31:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 18:12:07 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	infinite_loop(char *end, t_mini *m)
{
	char	*input;
	int		i;

	i = 3;
	while (1)
	{
		input = readline("heredoc> ");
		if (g_signal_flag[2] == 1 || ft_strncmp(input, end,
				ft_strlen(end)) == 0)
		{
			free(input);
			free_split(m->cmd);
			ft_listclear(&m->head, free);
			free_split(m->envm);
			while (i <= 1023)
				close(i++);
			exit(0);
		}
		write(m->fd_doc[1], input, ft_strlen(input));
		write(m->fd_doc[1], "\n", 1);
		free(input);
	}
}

void	here_doc(t_mini *m, char *end)
{
	int	pid;

	if (pipe(m->fd_doc) == -1)
		error_handle(m, "pipex: error pipe", "", 1);
	pid = fork();
	if (pid == -1)
		error_handle(m, "pipex: error fork", "", 1);
	if (pid == 0)
	{
		infinite_loop(end, m);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(m->fd_doc[1]);
		dup2(m->fd_doc[0], 0);
		close(m->fd_doc[0]);
	}
	close(m->fd_doc[0]);
	close(m->fd_doc[1]);
}
