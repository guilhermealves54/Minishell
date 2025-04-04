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

// Var Struct
typedef struct s_iter
{
	int		i;
	int		j;
	int		start;
	char	**av;
}	t_iter;

// Main Struct
typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**ap;
	char	**av;
	int		ppid;
	t_env	*export;
	int		exit_status;
}	t_mini;

// Funcs -----

// Printf_fd
int		ft_printf_fd(const char *format, ...);

// Initialization
t_mini	init(char **envp);
int		ft_getpid(void);
char	*get_input(char *prompt);

// Signal functions
void	setup_signals(void);

// Memory Clean
void	clean_list(t_mini *ms);

#endif
