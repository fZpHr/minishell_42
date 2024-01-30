/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:54:01 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/29 18:58:12 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>     // Pour printf
#include <stdlib.h>    // Pour malloc, free, exit
#include <unistd.h>    // Pour write, access, fork, execve, close, dup, dup2, pipe
#include <fcntl.h>     // Pour open
#include <sys/types.h> // Pour fork, wait, waitpid, wait3, wait4, signal
#include <sys/wait.h>  // Pour wait, waitpid, wait3, wait4
#include <signal.h>    // Pour signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/stat.h>  // Pour stat, lstat, fstat, unlink
#include <dirent.h>    // Pour opendir, readdir, closedir
#include <string.h>    // Pour strerror, perror
#include <termios.h>   // Pour tcsetattr, tcgetattr
#include <curses.h>    // Pour tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <sys/ioctl.h> // Pour ioctl
#include <pwd.h>       // Pour getcwd, chdir
#include <unistd.h>    // Pour isatty, ttyname, ttyslot
#include <stdlib.h>    // Pour getenv
#include <readline/readline.h> // Pour readline
#include <readline/history.h> // Pour add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
#include "../libft/libft.h"

typedef struct s_mini
{
	char	**cmd;
	char	*input;
	int		saved_stdin;
   	int		saved_stdout;
}				t_mini;


void 	error_handle(t_mini *m, char *str, int status);
void	free_end(t_mini *m, int status);
void	free_split(t_mini *m);
void	init(t_mini *m);
void	here_doc(t_mini *m, char *end);
void	stdin_stdout_handle(t_mini *m, int status);
void	ft_env(char **env);
void	ft_pwd(t_mini *m);

#endif
