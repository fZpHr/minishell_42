/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:31:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/23 15:06:08 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **ft_strdup_double_char(char **src, char *add, int i)
{
	char **dst;
	int j;

	j = 0;
	dst = malloc(sizeof(char *) * (i + 2));
	if (!dst)
		return (NULL);
	if (src)
	{
		while (j < i)
		{
			dst[j] = ft_strdup(src[j]);
			j++;
		}
		free_split(src);
	}
	dst[j] = ft_strdup(add);
	dst[j + 1] = NULL;
	return (dst);
}

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
			exit(0);	
		}
		//if (m->status_child == 0)
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
/* 		else
			write(m->fd[1], input, ft_strlen(input)); */
		free(input);
	}
}

/* void	infinite_loop(t_mini *m, char *end)
{
	char	*input;

	while (1)
	{
		input = readline("heredoc> ");
		if (ft_strncmp(input, end, ft_strlen(end)) == 0 || signal_flag == 1)
		{
			free(input);
			exit(0);
		}
		write(m->fd[1], input, ft_strlen(input));
		free(input);
	}
} */

/* void	infinite_loop(t_mini *m, char *end)
{
	char	*input;
	int i;

	i = 0;
	while (1)
	{
		//ft_putstr_fd("heredoc> ", 0);
		//input = get_next_line(0);
		input = readline("heredoc> ");
		if (ft_strncmp(input, end, ft_strlen(end)) == 0 || signal_flag == 1)
		{
			free(input);
			break;
		}
		if (m->end_status == 1)
		{
			m->current_input = ft_strdup_double_char(m->current_input, input, i);
			free(input);
		}
		else
		{
			ft_putstr_fd(input, m->fd[0]);
			free(input);
		}
		i++;
	}
	i = 0;
	if (m->end_status == 1)
		if (m->current_input)
		{
			while (m->current_input[i])
				printf("%s", m->current_input[i++]);
			free_split(&m->current_input);
		}

} */

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