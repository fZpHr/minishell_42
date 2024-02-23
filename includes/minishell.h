/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:54:01 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/23 18:09:53 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <pwd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern volatile sig_atomic_t	signal_flag[3];
// Parsing
typedef struct s_split_command
{
	char						**result;
	char						*current_group;
	int							i;
	int							j;
	int							result_index;
}								t_split_command;

typedef enum s_token
{
	COMMAND,
	ARGS,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC,
	END
}								t_token;

typedef struct s_token_list
{
	t_token						token;
	char						*value;
	struct s_token_list			*next;
}								t_token_list;

// Data

typedef struct s_mini
{
	int							status_exit;
	int							path_count;
	int							fd_save_heredoc[2];
	int							status_child;
	int							exit_fork;
	char						**cmd;
	char						**envm;
	char						**env_path;
	char						*path;
	char						*input;
	int							saved_stdin;
	int							saved_stdout;
	char						*pwd_cd;
	char						*old_pwd_cd;
	int							status;
	char						**cmd1;
	char						**cmd2;
	char						**envp;
	char						*tmp;
	char						*tmp_child;
	char						*tmp_end;
	int							exec;
	int							ac;
	int							exit_status;
	int							status_append;
	int							status_redir_out;
	char						*out;
	int							append_left;
	int							append_right;
	int							redi_left;
	int							redi_right;
	int							intern_last;
	int							count_cmd;
	int							alloc_env;
	int							alloc_cmd;
	int							alloc_cmd1;
	int							alloc_path;
	int							alloc_pwd;
	int							heredoc_status;
	int							end_status;
	char						**current_input;
	int							fd_doc[2];
	int							fd[2];
	int							parse;
	int							savefd[4];
}								t_mini;

// Signals

typedef struct s_sig
{
	int							sigint;
	int							sigquit;
	int							exit_status;
	pid_t						pid;
}								t_sig;

// Data
char							*cut_cmd_char(t_mini *m, char *cmd);
void							add_null(char **env, int i, int l);
int								ft_strlen_arg(char *str, char c);
int								check_if_pipe(char **cmd);
int								ft_space(char *str);
int								here_doc_check(t_mini *m, char *cmd);
void							ft_echo(t_mini *m, char **cmd);
void							ft_exec_builtin(t_mini *m);
int								build_intern(t_mini *m);
void							check_input(t_mini *m);
void							here_doc(t_mini *m, char *end);
void							ft_exec(t_mini *m, t_token_list *current);
int								ft_count_cmd(char *str, char c);
void							ft_cd(t_mini *m, char **cmd);
char							*target_path(t_mini *m, char **envp,
									char *target, int status);
void							ft_unset(t_mini *m);
void							ft_export(t_mini *m, char **env);
void							error_handle(t_mini *m, char *str, char *target,
									int status);
void							free_end(t_mini *m, int status);
void							free_split(char **cmd);
void							init(t_mini *m);
void							stdin_stdout_handle(t_mini *m, int status);
void							ft_env(t_mini *m, char **env, int status);
void							ft_pwd(t_mini *m);
void							ft_export(t_mini *m, char **env);
void							interrupt_handle(int sig);
char							*found_path(char **envp);
char							*found_cmd(t_mini *m, char **envp);
char							*found_var(char **envp, char *target);
int								ft_double_char_len(char **env);
void							cp_env(char **env, char **env_cp);

// Parsing

int								count_pipe(t_token_list *current);
void							lexing(char *whole_commands);
int								count_word_command(const char *command);
void							count_word_command_2(const char *command,
									int *i, int *count);
void							add_group_to_result(t_split_command *context);
char							*expand_variable(char *str, t_mini *m);
bool							is_inside_quotes(const char *command,
									int index);
void							handle_character(t_split_command *context,
									const char *command, int command_length);
char							**ft_split_command(const char *command);
int								skip_char(char c, const char *command, int i);
void							*my_realloc(void *ptr, size_t original_size,
									size_t new_size);
void							add_token(char **command_split,
									t_token_list **head, t_mini *m);
void							append_token_node(t_token_list **head,
									t_token token, char *value);
t_token_list					*create_token_node(t_token token, char *value);
const char						*get_token_name(t_token token);
void							free_token_list(t_token_list *head);
void							print_list(t_token_list *head);
t_token_list					*group_command_args(t_token_list *current,
									t_mini *mini);
int								get_number_of_args(t_token_list *current);
bool							is_between_quotes(char *str, int i);
char							*quote_things(char *str);
bool							is_meta_char_double_quotes(char c);
bool							is_meta_char_quote(char c, char quote);
t_token_list					*init_parsing(t_mini *m, t_token_list *current,
									t_token_list *head);
bool							check_wrong_command(t_token_list *current);
void							do_redir_in(char *file);
void							do_redir_out(char *file);
void							do_append(char *file);
bool							is_between_quotes(char *str, int i);
bool							is_between_double_quotes(char *str, int i);
void							ft_free_tab(char **tab);
char							*expand_variable_value(char *str, int i, int j,
									t_mini *m);
void							handle_token(t_token_list *current,
									t_mini *mini, int *i);

#endif
