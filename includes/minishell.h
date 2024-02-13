/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:54:01 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/13 13:52:56 by hbelle           ###   ########.fr       */
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
	int 	exit_fork;
	char	**cmd;
	char	**envm;
	char 	**env_path;
	char	*path;
	char	*input;
	int		saved_stdin;
   	int		saved_stdout;
	char	*pwd_cd;
	char	*old_pwd_cd;
	int 	status;
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	*tmp;
	char	*tmp_child;
	char	*tmp_end;
	int		exec;
	int		ac;
	int		exit_status;
	int		status_append;
	char	*out;
	int		append_left;
	int		append_right;
	int		redi_left;
	int		redi_right;
	int		intern_last;
	int		count_cmd;
	int 	alloc_env;
	int 	alloc_cmd;
	int		alloc_cmd1;
	int 	alloc_path;
	int 	alloc_pwd;
	int		heredoc_status;

}				t_mini;

/*typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	*tmp;
	char	*tmp_child;
	char	*tmp_end;
	int		exec;
	int		ac;

}			t_pipex;*/

void	ft_exec_builtin(t_mini *m, char *cmd, char **envp);
int		build_intern(t_mini *m, char *c);
void	check_input(t_mini *m);
void	here_doc(t_mini *m, char *end);
void	ft_exec(t_mini *m, char *input, char **envp);
int 	ft_count_cmd(char *str, char c);
void	ft_cd(t_mini *m, char **cmd);
char	*target_path(char **envp, char *target);
void	ft_unset(t_mini *m);
void	ft_export(t_mini *m, char **env);
void	error_handle(t_mini *m, char *str, char *target, int status);
void	free_end(t_mini *m, int status);
void	free_split(char **cmd);
void	init(t_mini *m);
void	stdin_stdout_handle(t_mini *m, int status);
void	ft_env(t_mini *m, char **env, int status);
void	ft_pwd(t_mini *m);
void	ft_echo(t_mini *m);
void	ft_export(t_mini *m, char **env);
void	interrupt_handle(int sig);
char	*found_path(char **envp);
char	*found_cmd(t_mini *m, char **envp, char *cmd);
char	*found_var(char **envp, char *target);
int		ft_double_char_len(char **env);
void	cp_env(char **env, char **env_cp);

#endif
