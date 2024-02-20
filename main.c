/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/20 19:13:38 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t signal_flag = 0;

void	interrupt_handle(int sig)
{
    if (sig == SIGINT)
    {
		signal_flag = 1;
		ft_putstr_fd("\n$>", 2);
    }
    else if (sig == SIGQUIT)
    {
        return;
    }
}

t_token_list	*init_parsing(t_mini *m, t_token_list *current, t_token_list *head)
{
	char			**command_split;

	command_split = ft_split_command(m->input);
	//head = current;
	add_token(command_split, &head, m);
	current = head;
	while (current->token != END)
	{
		current->value = expand_variable(current->value, m);
		//ft_putstr_fd(current->value, 1);
		current = current->next;
	}
	current = head;
	while (current->token != END)
	{
		current->value = quote_things(current->value);
		/* if (check_wrong_command(current) == false)
		{
			error_handle(m, "error", "", 1);
			m->parse = 1;
			return (NULL);
		} */
		current = current->next;
	}

	current = head;
	m->ac = count_pipe(current);
	current = head;
	//print_list(head);
	return (head);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction sa;

    sa.sa_handler = interrupt_handle;
    sa.sa_flags = SA_RESTART; // to restart functions if interrupted
    sigemptyset(&sa.sa_mask); // to empty the signal set
    sigaction(SIGINT, &sa, NULL); // ctrl + c
  	signal(SIGQUIT, SIG_IGN); // ignore ctrl + backslash*/

	(void)ac;
	(void)av;
	t_mini	m;
	t_token_list	*head;
	t_token_list *current;
	
	current = NULL;
	head = NULL;
	init(&m);
	ft_env(&m, env, 0);
 	m.savefd[0] = dup(0);
	m.savefd[1] = dup(1); 
	m.savefd[2] = dup(0);
	m.savefd[3] = dup(1); 
	while (1)
	{
		m.parse = 0;
		signal_flag = 0;
   	 	m.input = readline("$>");
		if (m.input)
			add_history(m.input);
		if (m.input == NULL) // ctrl + d
				error_handle(&m, "", "", 1000);
		else if (ft_space(m.input) == 0 && signal_flag == 0)
		{
			current = init_parsing(&m, current, head);
			if (ft_strcmp(m.input, "") != 0)
			{
				current = group_command_args(current, &m);
				if (m.parse == 0)
				{
					if ((ft_strcmp(m.cmd[0], "exit") == 0 ) && (check_if_pipe(m.cmd) == 0))
							error_handle(&m, "", "", 1000);
					else
						ft_exec(&m, current);
					if (current && current->token != END)
						current = current->next;
				}
			}
			free_split(&m.cmd);
		} 
		free(m.input);
		dup2(m.savefd[2], 0);
		dup2(m.savefd[3], 1);
	}
	return (0);
}