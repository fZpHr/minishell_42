/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmekhzou <tmekhzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:54:01 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/27 17:25:14 by tmekhzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define malloc(n) ft_malloc(n, __FILE__, __LINE__, __FUNCTION__)
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

extern volatile sig_atomic_t	g_signal_flag[3];
// Parsing

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
	char						**cmd;
	char						**envm;
	char						*path;
	char						*input;
	char						*pwd_cd;
	char						*old_pwd_cd;
	char						*tmp_child;
	char						*tmp_end;
	int							ac;
	int							exit_status;
	int							status_append;
	int							status_redir_out;
	int							alloc_env;
	int							heredoc_status;
	int							fd_doc[2];
	int							fd[2];
	int							parse;
	int							savefd[2];
	t_token_list				*head;
	int							error_open;
	int							parse_error;
	size_t						max_unset;
}								t_mini;

// Signals

typedef struct s_sig
{
	int							sigint;
	int							sigquit;
	int							exit_status;
	pid_t						pid;
}								t_sig;

typedef struct s_split_command
{
	int							result_size;
	int							result_capacity;
	char						**result;
	int							i;
	int							j;
	int							command_length;
	char						*current_group;
	int							in_single_quotes;
	int							in_double_quotes;
}								t_split_command;

// Data
void							init_parsing(t_mini *m, t_token_list **current);
void							loop_main(t_mini *m, t_token_list *current);
void							end(t_mini *m);
void							child_process(t_mini *m);
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
void							ft_env(t_mini *m, char **env, int status);
void							ft_pwd(t_mini *m);
void							ft_export(t_mini *m, char **env);
void							interrupt_handle(int sig);
char							*found_path(char **envp);
char							*found_cmd(t_mini *m, char **envp);
char							*found_var(char **envp, char *target);
int								ft_double_char_len(char **env);
void							cp_env(char **env, char **env_cp);
void							close_fds(t_mini *m);
void							*Malloc(size_t size, const char *file, int line,
									const char *function);
// Parsing

// redirections.c
void							do_redir_in(t_mini *m, char *file);
void							do_redir_out(char *file);
void							do_append(char *file);

// quotes.c
char							*handle_quotes(char *str, char *new_str, int *i,
									int *j);
char							*quote_things(char *str);
bool							is_between_quotes(char *str, int i);
bool							is_between_double_quotes(char *str, int i);

// parsing.c
bool							is_meta_char_quote(char c, char quote);
bool							check_wrong_command(t_token_list *current);
char							*expand_variable_value(char *str, int i, int j,
									t_mini *m);
char							*expand_variable(char *str, t_mini *m);
void							check_error_quotes(t_mini *m);

// linked_list.c
t_token_list					*create_token_node(t_token token, char *value);
void							append_token_node(t_token_list **head,
									t_token token, char *value);
void							free_token_list(t_token_list *head);
int								count_pipe(t_token_list *current);

// liexing.c
void							handle_less_than(char **command_split,
									t_token_list **head, t_mini *m, int *i);
void							handle_greater_than(char **command_split,
									t_token_list **head, t_mini *m, int *i);
void							add_token(char **command_split,
									t_token_list **head, t_mini *m);

// get_command_args.c
void							handle_token(t_token_list *current,
									t_mini *mini, int *i);
void							group_command_args(t_token_list **current,
									t_mini *mini);
int								get_number_of_args(t_token_list **current);

// check_input.c
void							ft_exec_builtin(t_mini *m);
int								build_intern(t_mini *m);
int								here_doc_check(t_mini *m, char *cmd);
int								ft_space(char *str);
int								check_if_pipe(char **cmd);

// utils/split_utils.c
int								count_word_command(const char *command);
void							count_word_command_2(const char *command,
									int *i, int *count);
void							handle_quotes_split(const char *command,
									t_split_command *sc);
void							handle_special_chars(const char *command,
									t_split_command *sc);
char							**ft_split_command(const char *command);
int								skip_char(char c, const char *command, int i);

// utils/parsing_split.c
void							handle_double_chars(const char *command,
									t_split_command *sc);
void							handle_single_char(const char *command,
									t_split_command *sc);
void							handle_space(const char *command,
									t_split_command *sc);
void							handle_regular_char(const char *command,
									t_split_command *sc);
void							add_current_group_result(t_split_command *sc);
void							increase_result_capacity(t_split_command *sc);
void							handle_end(t_split_command *sc);
void							ft_listclear(t_token_list **lst,
									void (*del)(void *));

void							print_list(t_token_list *head);
const char						*get_token_name(t_token token);

#endif
