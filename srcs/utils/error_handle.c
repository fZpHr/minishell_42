/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:58:56 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/22 12:27:40 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_handle(t_mini *m, char *str, char *target, int status, t_token_list *list)
{
	ft_putstr_fd("\033[0;31m", 2);
	if (status == 9999)
		m->exit_fork = 1;
	if (status >= 1000)
		m->exit_status = status - 1000;
	else
		m->exit_status = status << 8;
	if (status > 0)
	{
		//ft_putstr_fd(str, 2);
		printf("%s %s\n", str, target);
	}
    ft_putstr_fd("\033[0m", 2);
	if (status >= 1000)
    	free_end(m, m->exit_status, list);
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


