/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:45 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/31 17:54:45 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	interrupt_handle(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n$>", 4);
    }
    else if (sig == SIGQUIT)
    {
        return;
    }
}
