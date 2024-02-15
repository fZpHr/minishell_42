/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:31:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/15 18:15:07 by hbelle           ###   ########.fr       */
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
		//ft_putstr_fd("heredoc> ", 0);
		//input = get_next_line(0);
		input = readline("heredoc> ");
		if (ft_strncmp(input, end, ft_strlen(end)) == 0)
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
			free_split(m->current_input);
		}

}

/*void	infinite_loop_child(int fd[2], char *end)
{
	char	*input;
	int i;

	i = 0;
	while (1)
	{
		//printf("ici\n");
		//printf("end = %s\n", end);
		input = readline("heredoc> ");
		//ft_printf("ici:");
		//input = get_next_line(0);
		//ft_putstr_fd("ouga", 0);
		if (ft_strncmp(input, end, ft_strlen(end)) == 0)
		{
			free(input);
			break;
		}
		write(fd[1], input, ft_strlen(input));
		free(input);
		i++;
	}
}*/

void	here_doc(t_mini *m, char *cmd)
{
	//int pid;

	m->heredoc_status = 1;
	if (!cmd)
	{
		error_handle(m, "syntax error near unexpected token `newline'\n", "", 1);
		return ;
	}
	/*pid = fork();
	if (pid == -1)
	{
		error_handle(m, "error fork", "", 1);
		return ;
	}
	if (pid == 0)
	{*/
		infinite_loop(m, cmd);
	/*}
	else
		waitpid(pid, NULL, 0);*/
}	