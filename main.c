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


void	interrupt_handle(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n$>", 4);
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
    	if (ft_strcmp(m.cmd[0], "exit\n") == 0)
        	error_handle(&m, "", 0);
    	else if (ft_strcmp(m.cmd[0], "pwd\n") == 0)
        	ft_pwd(&m);
    	else if (ft_strcmp(m.cmd[0], "env\n") == 0)
        	ft_env(env);
    	else if (ft_strcmp(m.cmd[0], "<<\n") == 0)
    	{
        	stdin_stdout_handle(&m, 0);
        	here_doc(&m, m.cmd[1]);
        	stdin_stdout_handle(&m, 1);
    	}
    	free_split(&m);
    	free(m.input);
	}
	return (0);
}




/*while (1)
	{
		m.input = readline("$> ");
		if (interrupted)
    	{
        	interrupted = 0;
        	continue ;
    	}
		if (m.input && *m.input)
			add_history(m.input);
		m.cmd = ft_split(m.input, ' ');
		if (ft_strcmp(m.cmd[0], "exit\n") == 0)
			error_handle(&m, "", 0);
		else if (ft_strcmp(m.cmd[0], "") == 0)
			error_handle(&m, "\nCtrl+D détecté. Sortie.\n", 0);
		else if (ft_strcmp(m.cmd[0], "pwd\n") == 0)
			ft_pwd(&m);
		else if (ft_strcmp(m.cmd[0], "env\n") == 0)
			ft_env(env);
		else if (ft_strcmp(m.cmd[0], "<<") == 0)
		{
			stdin_stdout_handle(&m, 0);
			here_doc(&m, m.cmd[1]);
			//chose a faire avec le heredoc
			stdin_stdout_handle(&m, 1);
		}
		free_split(&m);
		free(m.input);
	}*/