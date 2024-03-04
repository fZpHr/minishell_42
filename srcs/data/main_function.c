/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/02/26 13:59:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/29 19:28:15 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	init_main(t_mini *m, t_token_list **current)
{
	*current = NULL;
	m->status_exit = 0;
	m->parse = 0;
	m->error_open = 0;
}

void	group_loop(t_mini *m, t_token_list **current)
{
	group_command_args(current, m);
	while (m->error_open == 1)
	{
		free_split(m->cmd);
		m->cmd = NULL;
		if ((*current))
			(*current) = (*current)->next;
		m->ac = m->ac - 1;
		group_command_args(current, m);
		if (m->cmd == NULL || m->error_open == 0)
			break ;
	}
}

void	else_if_main(t_mini *m, t_token_list *current)
{
	init_parsing(m, &current);
	if (ft_strcmp(m->input, "") != 0)
	{
		group_loop(m, &current);
		if (m->error_open == 1)
			m->parse = 1;
		if (m->parse == 0 && m->cmd != NULL)
		{
			if ((ft_strcmp(m->cmd[0], "exit") == 0)
				&& (check_if_pipe(m->cmd) == 0))
			{
				if (m->cmd[1])
					error_handle(m, "", "", 1000 + ft_atoi(m->cmd[1]));
				else
					error_handle(m, "", "", -1);
			}
			else if (m->cmd && m->cmd[0] && m->cmd[0][0] != '\0')
				ft_exec(m, current);
			if (current && current->token != END)
				current = current->next;
		}
	}
	free_split(m->cmd);
	ft_listclear(&m->head, free);
	free(m->head);
}

void	loop_main(t_mini *m, t_token_list *current)
{
	while (1)
	{
		init_main(m, &current);
		if (g_signal_flag[1] == 0)
			m->input = readline("$>");
		else
		{
			m->exit_status = 130;
			m->input = get_next_line(0);
			cut_extra_char(m->input);
		}
		g_signal_flag[1] = 0;
		g_signal_flag[2] = 0;
		check_error_quotes(m);
		if (m->input)
			add_history(m->input);
		if (m->input == NULL)
			error_handle(m, "", "", 9001);
		else if (ft_space(m->input) == 0 && m->parse_error == 0)
			else_if_main(m, current);
		while (waitpid(-1, &m->exit_status, WNOHANG) >= 0)
			;
		if (m->input)
			free(m->input);
		dup2(m->savefd[0], 0);
		dup2(m->savefd[1], 1);
	}
}
