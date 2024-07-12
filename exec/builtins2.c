/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:25 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/12 20:11:27 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *dta)
{
	if ((ft_strncmpp(dta->read[0], "exit", 4) == 0) && dta->read[0][4] == 0)
	{
		if (dta->read[1] == 0)
		{
			write(1, "exit\n", 5);
			g_exit_status = 0;
			exit(0);
		}
		if ((ft_strncmpp(dta->read[1], "0", 1) == 0) && dta->read[1][1] == 0)
		{
			write(1, "exit\n", 5);
			g_exit_status = 0;
			exit(0);
		}
		ft_exit2(dta);
	}
}

void	ft_exit2(t_data *dta)
{
	if (dta->read[1] != 0)
	{
		if (dta->read[2] != 0)
		{
			printf("exit\n");
			g_exit_status = 2;
			printf(RED "exit: too many arguments\n" RESET);
			return ;
		}
		if (ft_isalphaa(dta->read[1]) == 1)
		{
			printf(RED"exit : "RESET);
			printf(RED"%s: numeric argument required\n"RESET, dta->read[1]);
			g_exit_status = 2;
			exit(2);
		}
		else if (ft_atoi(dta->read[1]) != 0)
		{
			g_exit_status = ft_atoi(dta->read[1]);
			write(1, "exit\n", 5);
			exit(ft_atoi(dta->read[1]));
		}
	}
}

int	ft_cd(t_data *dta)
{
	if (dta->read[0] && dta->read[1] && !dta->read[2])
	{
		if ((ft_strncmpp(dta->read[0], "cd", 2) == 0) && dta->read[0][2] == 0)
		{
			if (chdir(dta->read[1]) == 0)
				return (0);
			else
			{
				perror(RED "Error cd " RESET);
				g_exit_status = 2;
				return (1);
			}
		}
	}
	return (0);
}

void	print_pwd(t_data *dta)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 404);
	if ((ft_strncmpp(dta->read[0], "pwd", 3) == 0) && dta->read[0][3] == 0
		&& dta->read[1] == 0)
	{
		if (getcwd(pwd, 404) != NULL)
			printf("%s\n", pwd);
	}
	free(pwd);
}
