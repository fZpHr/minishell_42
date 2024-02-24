/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:53:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/24 16:45:31 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t signal_flag[3];

void	interrupt_handle(int sig)
{
    if (sig == SIGINT)
    {
		signal_flag[0] = 1;
		signal_flag[1] = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		signal_flag[0] = 0;
    }
    else if (sig == SIGQUIT)
    {
        return;
    }
}

void	init_parsing(t_mini *m, t_token_list **current)
{
	char			**command_split;
	//t_token_list 	*head;

	command_split = ft_split_command(m->input);
	add_token(command_split, current, m);
	/* current = head; */
	//head = (*current);
	m->head = (*current);
	while ((*current)->token != END)
	{
		(*current)->value = expand_variable((*current)->value, m);
		//ft_putstr_fd(current->value, 1);
		(*current) = (*current)->next;
	}
	(*current) = m->head;
	while ((*current)->token != END)
	{
		(*current)->value = quote_things((*current)->value);
		/* if (check_wrong_command(current) == false)
		{
			error_handle(m, "error", "", 1);
			m->parse = 1;
			return (NULL);
		} */
		(*current) = (*current)->next;
	}
	(*current) = m->head;
	m->ac = count_pipe(*current);
	(*current) = m->head;
	while ((*current)->token != END)
	{
		if ((*current)->token == HERE_DOC && (*current)->next->next->token != COMMAND)
			m->ac = 0;
		(*current) = (*current)->next;
	}
	(*current) = m->head;
	free_split(command_split);
	//free(command_split);
	//print_list(*current);
}

const char	*get_token_name(t_token token)
{
	switch (token)
	{
	case COMMAND:
		return ("COMMAND");
	case PIPE:
		return ("PIPE");
	case APPEND:
		return ("APPEND");
	case REDIR_IN:
		return ("REDIR_IN");
	case REDIR_OUT:
		return ("REDIR_OUT");
	case END:
		return ("END");
	case HERE_DOC:
		return ("HERE_DOC");
	default:
		return ("UNKNOWN");
	}
}


void	print_list(t_token_list *head)
{
	t_token_list *current = head;

	while (current != NULL)
	{
		printf("Token: %s, Value: %s\n", get_token_name(current->token),
			current->value);
		current = current->next;
	}
	current = head;
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
	t_token_list *current;
	
	current = NULL;
	init(&m);
	ft_env(&m, env, 0);
 	m.savefd[0] = dup(0);
	m.savefd[1] = dup(1); 
	m.savefd[2] = dup(0);
	m.savefd[3] = dup(1); 
	while (1)
	{
		current = NULL;
		m.parse = 0;
		m.error_open = 0;
		if (signal_flag[1] == 0)
			m.input = readline("$>");
		else
			m.input = readline("");
		signal_flag[1] = 0;
		if (m.input)
			add_history(m.input);
		if (m.input == NULL) // ctrl + d
				error_handle(&m, "", "", 1000);
		else if (ft_space(m.input) == 0)
		{
			init_parsing(&m, &current);
			if (ft_strcmp(m.input, "") != 0)
			{
				group_command_args(&current, &m);
				if (m.error_open == 1)
					m.parse = 1;
				if (m.parse == 0 && m.cmd[0] != NULL)
				{
					if ((ft_strcmp(m.cmd[0], "exit") == 0 ) && (check_if_pipe(m.cmd) == 0))
							error_handle(&m, "", "", 1000);
					else
						ft_exec(&m, current);
					if (current && current->token != END)
						current = current->next;
				}
			}
			//print_list(m.head);
			free_split(m.cmd);
			ft_listclear(&m.head, free);
			//free(current);
			free(m.head);
		}
		while (waitpid(-1, &m.exit_status, WNOHANG) == 0);
		free(m.input);
		dup2(m.savefd[2], 0);
		dup2(m.savefd[3], 1);
	}
	return (0);
}