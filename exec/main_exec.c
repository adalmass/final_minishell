/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:40 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 19:39:51 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_redi2(t_data *dta, char **envp)
{
	if (count_redir(dta->exec[0], '>'))
	{
		dta->redi = ft_splitt(dta->exec[0], '>');
		dta->free_redi = dta->redi;
	}
	else if (count_redir(dta->exec[0], '<'))
	{
		dta->rredi = ft_splitt(dta->exec[0], '<');
		dta->free_rredi = dta->rredi;
	}
	handl_exec4(dta, envp);
	if (dta->free_var != NULL)
	{
		free_double_tab(dta->read);
		dta->free_var = NULL;
	}
}

void	init_struct_redi3(t_data *dta)
{
	if (dta->free_var != NULL)
	{
		free_double_tab(dta->read);
		dta->free_var = NULL;
	}
	if (dta->free_redi != NULL)
	{
		free_double_tab(dta->redi);
		dta->free_redi = NULL;
	}
	if (dta->free_rredi != NULL)
	{
		free_double_tab(dta->rredi);
		dta->free_rredi = NULL;
	}
}

void	init_struct_redi(t_data *dta, char **envp)
{
	if (dta->exec[1] != 0)
	{
		init_struct_redi3(dta);
		multi_pipe(dta, envp);
		if (dta->free_redi != NULL)
		{
			free_double_tab(dta->redi);
			dta->free_redi = NULL;
		}
		if (dta->free_rredi != NULL)
		{
			free_double_tab(dta->rredi);
			dta->free_rredi = NULL;
		}
	}
	else if (dta->exec[1] == 0)
		init_struct_redi2(dta, envp);
}

void	handl_exec5(t_data *dta, char **envp)
{
	if ((dta->redi[1] != 0) && dta->exec[1] == 0)
	{
		handl_redirect2(dta, envp);
		if (dta->free_redi != NULL)
		{
			free_double_tab(dta->redi);
			dta->free_redi = NULL;
		}
	}
	else if ((ft_strncmpp(&dta->read[0][0], ">", 1) == 0)
		|| dta->redi[1] != 0)
	{
		check_redirect(dta);
		if (dta->free_redi != NULL)
		{
			free_double_tab(dta->redi);
			dta->free_redi = NULL;
		}
	}
}

void	handl_exec4(t_data *dta, char **envp)
{
	if (count_redir(dta->exec[0], '<'))
	{
		if (ft_strncmpp(&dta->read[0][0], "<", 1) == 0)
		{
			reverse_redirect(dta);
			if (dta->free_rredi != NULL)
			{
				free_double_tab(dta->rredi);
				dta->free_rredi = NULL;
			}
		}
		else if ((dta->rredi[1] != 0) && dta->exec[1] == 0)
		{
			check_reverse_redirect(dta, envp);
			if (dta->free_rredi != NULL)
			{
				free_double_tab(dta->rredi);
				dta->free_rredi = NULL;
			}
		}
	}
	else if (count_redir(dta->exec[0], '>'))
		handl_exec5(dta, envp);
	else
		take_exec(dta, envp);
}
