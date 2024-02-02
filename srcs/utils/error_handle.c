/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:58:56 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/02 16:57:30 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void error_handle(t_mini *m, char *str, char *target, int status)
{
	char *error_message;

	target = NULL;
    ft_putstr_fd("\033[0;31m", 2);
	if (status > 0)
	{
		printf("%s", str);
		printf("%s\n", target);
   		error_message = strerror(status);
    	if (error_message != NULL)
    	    printf("%s", error_message);
  		else
    	    perror(NULL);
	}
    ft_putstr_fd("\033[0m", 2);
    free_end(m, status);
}

void handle_error(t_pipex *p, char *str, char *target, int status)
{
	char *error_message;

	(void)p;
	target = NULL;
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
	exit (status);
    //free_end(p, status);
}

void	error_handle_str2(t_mini *m, char *str, char *target, char *str2)
{
	char *error_message;

	target = NULL;
    ft_putstr_fd("\033[0;31m", 2);
	printf("%s", str);
	printf("%s\n", target);
   	error_message = strerror(1);
    if (error_message != NULL)
    	printf("%s", error_message);
  	else
    	    perror(NULL);
	}
    ft_putstr_fd("\033[0m", 2);
    free_end(m, status);
}


