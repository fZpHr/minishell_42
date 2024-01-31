/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/29 19:25:05 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	cut_newline(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i][ft_strlen(str[i]) - 1] == '\n')
			str[i][ft_strlen(str[i]) - 1] = '\0';
		i++;
	}
}

void 	ft_export(t_mini *m)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (m->cmd[i])
	{
		j = 0;
		while (m->cmd[i][j])
		{
			if (m->cmd[i][j] == '=')
			{
				tmp = ft_substr(m->cmd[i], 0, j);
				if (ft_isalpha(tmp[0]) == 0)
					error_handle(m, "export: not an identifier\n", 1);
				free(tmp);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
    struct sigaction sa;
    sa.sa_handler = interrupt_handle;
    sa.sa_flags = SA_RESTART; // to restart functions if interrupted
    sigemptyset(&sa.sa_mask); // to empty the signal set
    sigaction(SIGINT, &sa, NULL); // ctrl + c
  	signal(SIGQUIT, SIG_IGN); // ignore ctrl + backslash

	(void)ac;
	(void)av;
	t_mini	m;
	init(&m);
	while (1)
	{
		write(1, "$>", 3);
   	 	m.input = get_next_line(0);
    	if (m.input == NULL) // ctrl + d
    	{
			printf("\n");
        	free(m.input);
        	exit(0);
   		}
    	/*if (m.input && *m.input)
       		add_history(m.input);*/
    	m.cmd = ft_split(m.input, ' ');
		cut_newline(m.cmd);
    	if (ft_strcmp(m.cmd[0], "exit") == 0)
        	error_handle(&m, "", 0);
    	else if (ft_strcmp(m.cmd[0], "pwd") == 0)
        	ft_pwd(&m);
    	else if (ft_strcmp(m.cmd[0], "env") == 0)
        	ft_env(env);
    	else if (ft_strcmp(m.cmd[0], "<<") == 0)
    	{
        	stdin_stdout_handle(&m, 0);
        	here_doc(&m, m.cmd[1]);
        	stdin_stdout_handle(&m, 1);
    	}
		else if (ft_strcmp(m.cmd[0], "echo") == 0)
			ft_echo(&m);
		else if (ft_strcmp(m.cmd[0], "export") == 0)
			ft_export(&m);
    	free_split(&m);
    	free(m.input);
	}
	return (0);
}