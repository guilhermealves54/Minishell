/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:40:10 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/14 14:20:07 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			exitcode(t_mini *ms, int n, int *quit);
static int			ft_isdigitsignal(char *str);
static long long	ft_atoll(const char *str, int *overf);
static long long	atolloop(const char *str, int **overf, int *sign, int i);

int	exec_exit(t_mini *ms, int n)
{
	int	quit;
	int	exit_code;

	if (ms->cmd[n].input_fd != STDIN_FILENO
		|| ms->cmd[n].output_fd != STDOUT_FILENO)
		quit = 0;
	else
	{
		quit = 1;
		printf("exit\n");
	}
	exit_code = exitcode(ms, n, &quit);
	if (quit == 1)
	{
		clean_list(ms);
		free_2strings(ms->prompt, ms->input);
		split_memfree(ms);
		exit(exec_free(ms, 0, FREE_STRUCT | FREE_CMD, exit_code));
	}
	return (exit_code);
}

static int	exitcode(t_mini *ms, int n, int *quit)
{
	int			i;
	int			overf;
	long long	ret;
	char		*s;

	i = 0;
	while (ms->cmd[n].cmd[i])
		i++;
	if (i == 1)
		return (0);
	overf = 0;
	s = get_new_str(ms->cmd[n].cmd[1]);
	ret = ft_atoll(s, &overf);
	if ((!ft_isdigitsignal(s) || overf))
		return (printf(
				"Minishell: exit: %s: numeric argument required\n",
				s), free(s), 2);
	if (i > 2)
		return (*quit = 0, printf(
				"Minishell: exit: too many arguments\n"), free(s), 1);
	free(s);
	return (ret % 256);
}

static int	ft_isdigitsignal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
			i++;
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

static long long	ft_atoll(const char *str, int *overf)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	return (atolloop(str, &overf, &sign, i));
}

static long long	atolloop(const char *str, int **overf, int *sign, int i)
{
	unsigned long long	res;
	unsigned long long	maxneg;

	res = 0;
	maxneg = (unsigned long long)LLONG_MAX + 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (*sign == 1 && res > LLONG_MAX)
		{
			res = LLONG_MAX;
			**overf = 1;
			return (res);
		}
		else if (*sign == -1 && res > maxneg)
		{
			res = LLONG_MIN;
			**overf = 1;
			return (res);
		}
		i++;
	}
	return (res * *sign);
}
