/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:49:21 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/14 22:41:55 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handl_exec(t_data *dta, char **envp)
{
	if (ft_strncmpp(dta->read[0], "pwd", 4) == 0)
		print_pwd(dta);
	else if (ft_strncmpp(dta->read[0], "env", 4) == 0)
		print_env(dta, envp);	
	else if (ft_strncmpp(dta->read[0], "env", 4) != 0
			&& ft_strncmpp(dta->read[0], "pwd", 4) != 0)
		handl_exec2(dta, envp);
}
void	print_echo_basic(t_data *dta, int i, int len)
{
	printf("%s", dta->read[i]);
	if (i != len - 1)
		printf(" ");
}

void	handl_dollar(t_data *dta, int i, int len)
{
	while (i < len)
	{
		if (dta->read[i][0] == '$' && dta->read[i][1] != 0)
		{
			if (dta->read[i][1] == '?')
			{
				if (search_dollar(dta, i) == 0)
					dollar_what(dta);
				else
					printf("%s ", dta->read[i]);
				break ;
			}
			else if (search_dollar(dta, i) == 0)
				take_var2(dta, i);
			else
				printf("%s ", dta->read[i]);
		}
		else
			print_echo_basic(dta, i , len);
		i++;
	}
	g_exit_status = 0;
	printf("\n");
}

void	handl_exec2(t_data *dta, char **envp)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	while (dta->read[len])
		len++;
	if (ft_strncmpp(dta->read[0], "echo\0", 5) == 0
		&& dta->read[1] != 0)
	{
		if (dta->read[1][0] == '-' && dta->read[1][1] == 'n')
		{
			print_echo(dta);
			g_exit_status = 0;
		}
		else 
		{
			handl_dollar(dta, i, len);
			g_exit_status = 0;
		}
	}
	else
		handl_exec3(dta, envp);
}

void	handl_exec3(t_data *dta, char **envp)
{
	if (ft_strncmpp(dta->read[0], "cd", 3) == 0)
		ft_cd(dta);
	else if (ft_strncmpp(dta->read[0], "exit", 5) == 0)
		ft_exit(dta);
	else if (ft_strncmpp(dta->read[0], "export", 7) == 0)
		ft_export(dta);
	else if (ft_strncmpp(dta->read[0], "unset", 6) == 0)
		ft_unset(dta, envp);
	else
		init_struct_redi(dta, envp);
}
