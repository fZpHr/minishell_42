/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:54:01 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/02 16:22:26 by hbelle           ###   ########.fr       */
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
	char	**envm;
	char 	**env_path;
	char	*path;
	char	*input;
	int		saved_stdin;
   	int		saved_stdout;
	int 	env_md;
	char	*pwd_cd;
	char	*old_pwd_cd;
	
}				t_mini;

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	*tmp;
	char	*tmp_child;
	char	*tmp_end;
	int		exec;
	int		ac;

}			t_pipex;

void	error_handle_str2(t_mini *m, char *str, char *target, char *str2);
void	ft_cd(t_mini *m);
char	*target_path(char **envp, char *target);
void	ft_unset(t_mini *m);
void	ft_export(t_mini *m, char **env);
void	handle_error(t_pipex *p, char *str, char *target, int status);
void	error_handle(t_mini *m, char *str, char *target, int status);
void	free_end(t_mini *m, int status);
void	free_split(char **cmd);
void	init(t_mini *m);
void	init_p(t_pipex *p);
void	here_doc(t_mini *m, char *end);
void	stdin_stdout_handle(t_mini *m, int status);
void	ft_env(t_mini *m, char **env, int status);
void	ft_pwd(t_mini *m);
void	ft_echo(t_mini *m);
void	ft_export(t_mini *m, char **env);
void	interrupt_handle(int sig);
char	*found_path(char **envp);
char	*found_cmd(t_pipex *p, char **envp, char *cmd);
char	*found_var(char **envp, char *target);
int		ft_double_char_len(char **env);
void	cp_env(char **env, char **env_cp);
int		ft_exec(int argc, char **argv, char **envp);

#endif
