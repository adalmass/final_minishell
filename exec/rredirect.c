/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rredirect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:51 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/10 14:15:38 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void     check_reverse_redirect(t_data *dta)
{
	int j;

	j = 0;
	while(dta->exec[0][j])
	{
		if (dta->exec[0][j] == '<' && dta->exec[0][j + 1] != '<')
		{
			handl_redirect_input2(dta);
			break ;
		}
		else if (dta->exec[0][j] == '<' && dta->exec[0][j + 1] == '<')
		{			
			handl_rredirect(dta);
			break ;
		}
		j++;
	}
}

void    reverse_redirect(t_data *dta)
{
	if(ft_strncmpp(&dta->read[0][0], "<", 1) == 0)
	{
		if(ft_strncmpp(&dta->read[0][1], "<", 1) == 0)
		{
			if(dta->rredi[0] != 0)
			{
				dta->rredi[0] = ft_strtrim(dta->rredi[0], " ");
				prompt_rredirect(dta);
			}
			else
			{
				g_exit_status = 2;
				printf("minishell : syntax error near unexpected token `newline'\n");
			}
		}
	}
}

void    prompt_rredirect(t_data *dta)
{
	int		limit_found;
	int		lenn;
	char	*temp;

	limit_found = 0;
	temp = NULL;
	handl_prompt();
	dta->rredi[0] = ft_strtrim(dta->rredi[0], " ");
	lenn = ft_strlenn(dta->rredi[0]) + 1;
	while (limit_found == 0)
	{
		temp = readline("> ");
		if(ft_strncmpp(temp, dta->rredi[0], lenn) == 0)
			limit_found = 1;
	}
	if (temp)
		free (temp);
}

void	prompt_redirect4(t_data *dta)
{
	int		limit_found;
	char	*temp;
	int		lenn;

	limit_found = 0;
	temp = NULL;
	handl_prompt();
	lenn = ft_strlenn(dta->str[0]) + 1;
	while (limit_found == 0)
	{
		temp = readline("> ");
		if (!temp)
			return ;
		if (ft_strncmpp(temp, dta->str[0], lenn) == 0)
		{
			printf("\n");
			exec_rredirect3(dta);
			limit_found = 1;
		}
	}
	if (temp)
		free (temp);
}
