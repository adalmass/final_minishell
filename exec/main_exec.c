/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:40 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/14 18:09:59 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handl_env(t_data *dta, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	dta->cpy_envp = malloc(sizeof(char *) * i);
	i = 0;
	while (envp[i])
	{
		dta->cpy_envp[i] = ft_strdupp(envp[i]);
		i++;
	}
}

void	init_struct_redi(t_data *dta, char **envp)
{
	if (dta->exec[1] != 0)
		multi_pipe(dta, envp);
	if (dta->exec[1] == 0)
	{
		if (count_redir(dta->exec[0], '>'))
			dta->redi = ft_splitt(dta->exec[0], '>');
		else if (count_redir(dta->exec[0], '<'))
			dta->rredi = ft_splitt(dta->exec[0], '<');
		handl_exec4(dta, envp);
	}
}

void	handl_exec4(t_data *dta, char **envp)
{
	if (count_redir(dta->exec[0], '<'))
	{
		if (ft_strncmpp(&dta->read[0][0], "<", 1) == 0)
			reverse_redirect(dta);
		else if ((dta->rredi[1] != 0) && dta->exec[1] == 0)
			check_reverse_redirect(dta, envp);
	}
	else if (count_redir(dta->exec[0], '>'))
	{
		if ((dta->redi[1] != 0) && dta->exec[1] == 0)
			handl_redirect2(dta, envp);
		else if ((ft_strncmpp(&dta->read[0][0], ">", 1) == 0)
			|| dta->redi[1] != 0)
			check_redirect(dta);
	}
	else
		take_exec(dta, envp);
}

void	handl_prompt(void)
{
	signal(SIGINT, handl_signals);
	signal(SIGQUIT, handl_signals);
}
