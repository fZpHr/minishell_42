/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:58:56 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/12 18:54:35 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_handle(t_mini *m, char *str, char *target, int status)
{
    ft_putstr_fd("\033[0;31m", 2);
	if (status >= 1000)
		m->exit_status = status - 1000;
	else
		m->exit_status = status;
	if (status > 0)
		printf("%s %s\n", str, target);
    ft_putstr_fd("\033[0m", 2);
	if (status >= 1000)
    	free_end(m, m->exit_status);
}

/*void handle_error(t_pipex *p, char *str, char *target, int status)
{
	//char *error_message;

	(void)p;
    ft_putstr_fd("\033[0;31m", 2);
	if (status > 0)
	{
		printf("%s", str);
		printf("%s\n", target);
   		error_message = strerror(status);
   		printf("%s: ", str);
    	if (error_message != NULL)
    	    printf("%s", error_message);
  		else
    	    perror(NULL);*/
	/**}
    ft_putstr_fd("\033[0m", 2);
	exit (status);
    //free_end(p, status);
}*/


