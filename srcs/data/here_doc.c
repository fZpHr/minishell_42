/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:31:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/07 13:40:38 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	infinite_loop(int fd[2], char *end)
{
	char	*input;

	while (1)
	{
		ft_printf("pipe heredoc> ");
		input = get_next_line(0);
		if (ft_strncmp(input, end, ft_strlen(end)) == 0)
		{
			free(input);
			break;
		}
		write(fd[1], input, ft_strlen(input));
		free(input);
	}
}

void	here_doc(t_mini *m, char *end)
{
	int	fd[2];
	int	pid;

	if (end == NULL)
	{
		error_handle(m, "syntax error near unexpected token `newline'\n", "", 1);
		return ;
	}
	if (pipe(fd) == -1)
	{
		error_handle(m, "pipe error\n", "", 1);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		error_handle(m, "pipe error\n", "", 1);
		return ;
	}
	if (pid == 0)
	{
		infinite_loop(fd, end);
		error_handle(m, "", "", 0);
	}
	else
	{
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
	close(fd[0]);
	close(fd[1]);
}