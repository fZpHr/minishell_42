/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/26 14:47:45 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	else_if_main(t_mini *m, t_token_list *current)
{
	init_parsing(m, &current);
	if (ft_strcmp(m->input, "") != 0)
	{
		group_command_args(&current, m);
		if (m->error_open == 1)
			m->parse = 1;
		if (m->parse == 0 && m->cmd[0] != NULL)
		{
			if ((ft_strcmp(m->cmd[0], "exit") == 0)
				&& (check_if_pipe(m->cmd) == 0))
				error_handle(m, "", "", 1000 + ft_atoi(m->cmd[1]));
			else
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
		current = NULL;
		m->parse = 0;
		m->error_open = 0;
		if (g_signal_flag[1] == 0)
			m->input = readline("$>");
		else
			m->input = readline("");
		g_signal_flag[1] = 0;
		if (m->input)
			add_history(m->input);
		if (m->input == NULL)
			error_handle(m, "", "", 9001);
		else if (ft_space(m->input) == 0)
			else_if_main(m, current);
		while (waitpid(-1, &m->exit_status, WNOHANG) == 0)
			;
		free(m->input);
		dup2(m->savefd[2], 0);
		dup2(m->savefd[3], 1);
	}
}
