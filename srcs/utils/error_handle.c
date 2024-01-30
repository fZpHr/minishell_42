/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:58:56 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/17 16:39:48 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void error_handle(t_mini *m, char *str, int status)
{
	char *error_message;

    ft_putstr_fd("\033[0;31m", 2);
	if (status > 0)
	{
		printf("%s", str);
   		error_message = strerror(status);
   		printf("%s: ", str);
    	if (error_message != NULL)
    	    printf("%s", error_message);
  		else
    	    perror(NULL);
	}
    ft_putstr_fd("\033[0m", 2);
    free_end(m, status);
}