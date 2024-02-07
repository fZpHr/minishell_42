/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/07 14:22:55 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	ft_env(&m, env, 0);
	while (1)
	{
   	 	m.input = readline("$>");
		if (m.input)
			add_history(m.input);
    	if (m.input == NULL) // ctrl + d
			error_handle(&m, "", "", 1000);
		else if (ft_strcmp(m.input, "") != 0)
		{
			m.cmd = ft_split(m.input, ' ');
			check_input(&m);
    		if (ft_strcmp(m.cmd[0], "exit") == 0)
        		error_handle(&m, "", "", 1000);
    		else if (ft_strcmp(m.cmd[0], "pwd") == 0)
        		ft_pwd(&m);
    		else if (ft_strcmp(m.cmd[0], "env") == 0)
        		ft_env(&m, env, 1);
    		else if (ft_strcmp(m.cmd[0], "<<") == 0)
    		{
        		stdin_stdout_handle(&m, 0);
        		here_doc(&m, m.cmd[1]);
        		stdin_stdout_handle(&m, 1);
    		}
			else if (ft_strcmp(m.cmd[0], "echo") == 0)
				ft_echo(&m);
			else if (ft_strcmp(m.cmd[0], "export") == 0)
				ft_export(&m, env);
			else if (ft_strcmp(m.cmd[0], "unset") == 0)
				ft_unset(&m);
			else if (ft_strcmp(m.cmd[0], "cd") == 0)
				ft_cd(&m);
			else
				ft_exec(&m, m.input, env);
			free_split(m.cmd);
    		free(m.input);
		}
	}
	return (0);
}