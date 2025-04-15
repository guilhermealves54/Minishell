/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:47 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/04 18:20:47 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define FREE_BASE		1
# define FREE_STRUCT	2
# define FREE_CMD		4
# define FREE_PIPES		8
# define FREE_FDS		16
# define FREE_PIDS		32

// Includes
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <unistd.h>
# include "../libft/libft.h"

// Structs -----

// Envp list
typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// Var Structs
typedef struct s_iter
{
	int		i;
	int		j;
	int		start;
	char	**av;
}	t_iter;

//	Used in expand.c
typedef struct s_exp
{
	char	*first;
	char	*last;
	char	*var;
	int		start;
	char	*content;
}	t_exp;

//	Command struct
typedef struct s_cmd
{
	int		index;
	char	**cmd;
	char	*path;
	int		input_fd;
	int		output_fd;
	int		sts;
	int		builtin;
}	t_cmd;

// Main Struct
typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**ap;
	char	**av;
	char	**envp;
	int		ppid;
	int		input_rec;
	int		**fds;
	int		*pid;
	t_env	*export;
	t_exp	expand;
	t_cmd	*cmd;
	int		exit_status;
}	t_mini;

//	Global Variables
extern int	g_childrun;

//	Funcs

//	Printf_fd
int		ft_printf_fd(const char *format, ...);

//	Initialization
t_mini	init(char **envp);
int		ft_getpid(void);
char	*get_input(char *prompt);

//	Signals
void	setup_signals(void);

//	Expand
char	*expand(char *s, t_mini *ms);

//	Parsing
int		parsing(t_mini *mini);

//	Execute CMD
void	execute_cmd(t_mini *ms);
void	fork_proc(t_mini *ms, int proc, int pipes);
int		**crt_pipes(t_mini *ms, int pipes);
int		*crt_pid_arr(t_mini *ms, int pid_n, int pipes);
void	child_proc(t_mini *ms, int n, int pipes);

//	Builtins
void	print_echo(char **av);

//	Helper functions
char	**ft_split_quotes(char *s, char c);
char	*get_str(char *s, int start, int end);
void	update_i(char *s, int *i, char c);
int		check_closed_quotes(char *input);
int		char_quotes(char c);
char	*ft_getenv(char *var, t_mini *ms);
char	*ft_strjoin_3(char *path, char *cmd, char c);
char	*get_new_str(char *s);
int		cnt_strings(char **av);
int		pidnbr_cnt(t_mini *ms, int proc);

//	Memory Clean
void	clean_list(t_mini *ms);
void	free_mem(char **av);
void	split_memfree(t_mini *ms);
void	free_2strings(char *s1, char *s2);
void	close_pipes(t_mini *ms, int pipes);
int		exec_free(t_mini *ms, int pipes, int opt, int ret);
void	free_intarray(t_mini *ms, int pipes);

#endif
