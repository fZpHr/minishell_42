/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:31:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/14 19:26:52 by hbelle           ###   ########.fr       */
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


void	infinite_loop(t_mini *m, char *end)
{
	char	*input;
	int i;

	i = 0;
	while (1)
	{
		input = readline("> ");
		if (ft_strncmp(input, end, ft_strlen(end)) == 0)
		{
			free(input);
			break;
		}
		if (m->end_status == 0)
			printf("%s\n", input);
		else
			m->current_input = ft_strdup_double_char(m->current_input, input, i);
		free(input);
		i++;
	}
	if (m->end_status == 1)
	{
		i = 0;
		while(m->current_input[i])
			printf("%s\n", m->current_input[i++]);
		free_split(m->current_input);
	}

}

void	here_doc(t_mini *m, char *cmd)
{
	int	fd[2];
	int	pid;
	char **input;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	input = ft_split(cmd, " ");
	if (input[1] == NULL)
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
		infinite_loop(m, input[1]);
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