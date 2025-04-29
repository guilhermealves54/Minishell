/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:40:10 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/29 15:08:08 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			exitcode(t_mini *ms, int n);
static int			ft_isdigitsignal(char *str);
static long long	ft_atoll(const char *str, int *overf);
static long long	atolloop(const char *str, int **overf, int *sign, int i);

void	exec_exit(t_mini *ms, int n)
{
	printf("exit\n");
	if (exitcode(ms, n) != -1)
	{
		clean_list(ms);
		free_2strings(ms->prompt, ms->input);
		split_memfree(ms);
		exit(exec_free(ms, 0, FREE_STRUCT | FREE_CMD, exitcode(ms, n)));
	}
}

static int	exitcode(t_mini *ms, int n)
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
	else if (i > 2)
		return (printf("Minishell: exit: too many arguments\n"), -1);
	i = 0;
	overf = 0;
	s = get_new_str(ms->cmd[n].cmd[1]);
	ret = ft_atoll(s, &overf);
	if (!ft_isdigitsignal(s) || overf)
		return (printf(
				"Minishell: exit: %s: numeric argument required\n",
				s), free(s), 2);
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
