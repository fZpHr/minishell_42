/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:47:04 by tmekhzou          #+#    #+#             */
/*   Updated: 2024/02/27 17:45:20 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_double_chars(const char *command, t_split_command *sc)
{
	if (sc->current_group != NULL)
	{
		add_current_group_result(sc);
	}
	sc->result[sc->result_size] = ft_malloc(3);
	sc->result[sc->result_size][0] = command[sc->i];
	sc->result[sc->result_size][1] = command[sc->i + 1];
	sc->result[sc->result_size][2] = '\0';
	sc->result_size++;
	sc->i++;
}

void	handle_single_char(const char *command, t_split_command *sc)
{
	if (sc->current_group != NULL)
	{
		add_current_group_result(sc);
	}
	sc->result[sc->result_size] = ft_malloc(2);
	sc->result[sc->result_size][0] = command[sc->i];
	sc->result[sc->result_size][1] = '\0';
	sc->result_size++;
}

void	handle_space(const char *command, t_split_command *sc)
{
	(void)command;
	if (sc->current_group != NULL)
	{
		add_current_group_result(sc);
	}
}

void	handle_regular_char(const char *command, t_split_command *sc)
{
	if (sc->current_group == NULL)
	{
		sc->current_group = ft_malloc(sc->command_length - sc->i + 2);
		sc->j = 0;
	}
	sc->current_group[sc->j] = command[sc->i];
	sc->j++;
	sc->current_group[sc->j] = '\0';
}

void	add_current_group_result(t_split_command *sc)
{
	sc->result[sc->result_size] = ft_strdup(sc->current_group);
	sc->result_size++;
	free(sc->current_group);
	sc->current_group = NULL;
}
