/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/15 16:23:52 by hbelle           ###   ########.fr       */
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
		//m.input = get_next_line(0);
   	 	m.input = readline("$>");
		if (m.input)
			add_history(m.input);
		if (m.input == NULL) // ctrl + d
				error_handle(&m, "", "", 1000);
		else if (ft_space(m.input) == 0)
		{
			if (ft_strcmp(m.input, "") != 0)
			{
				m.cmd = ft_split(m.input, " ");
				if ((ft_strcmp(m.cmd[0], "exit") == 0 ) && (check_if_pipe(m.cmd) == 0))
						error_handle(&m, "", "", 1000);
				else
					ft_exec(&m, m.input, env);
			}
			free_split(m.cmd);
		}
		free(m.input);
	}
	return (0);
}