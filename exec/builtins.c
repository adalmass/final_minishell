/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:21 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/14 15:17:03 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data *dta, char **envp)
{
	(void) envp;
	int	i;

	i = 0;
	if ((ft_strncmpp(dta->read[0], "env\0", 4) == 0) && dta->read[1] == 0)
	{
		while (dta->cpy_envp[i])
		{
			printf("%s\n", dta->cpy_envp[i]);
			i++;
		}
		g_exit_status = 0;
	}
}

void	print_echo(t_data *dta)
{
	if ((ft_strncmpp(dta->read[0], "echo\0", 5) == 0)
		&& dta->read[1] != 0)
	{
		if (ft_strncmpp(dta->read[1], "-n", 2) == 0)
		{
			if (check_echo_n(dta) == 0)
				print_echo2(dta);
			else if (check_echo_n(dta) == 1)
				print_echo3(dta);
		}
		g_exit_status = 0;
	}
}

void	print_echo2(t_data *dta)
{
	int	i;
	int	lenn;

	i = 2;
	lenn = 0;
	while (dta->read[lenn])
		lenn++;
	if (check_echo_n(dta) == 0 && dta->read[i] != 0)
	{
		while (i < lenn)
		{
			if (dta->read[i][0] == '-' && dta->read[i][1] == 'n')
			{
				if (check_echo_n2(dta, i) == 1)
					break ;
			}
			else
				break ;
			i++;
		}
		print_echo_n(dta, i);
	}
}

void	print_echo3(t_data *dta)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (dta->read[len])
		len++;
	while (i <= len - 1)
	{
		if (dta->read[1] == 0)
			break ;
		else
		{
			i++;
			while (i <= len - 1)
			{
				printf("%s", dta->read[i]);
				if (i != len - 1)
					printf(" ");
				i++;
			}
			printf("\n");
		}
		i++;
	}
}
