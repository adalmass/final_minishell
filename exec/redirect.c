/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:48 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/14 19:44:46 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file(t_data *dta)
{
	if (access(dta->str[0], R_OK) == -1)
	{
		g_exit_status = 2;
		perror("Error ");
		return (1);
	}
	else
		return (0);
}

void	check_redirect(t_data *dta)
{
	char *temp;

	if (dta->read[0][0] == '>' && dta->read[0][1] == '>')
	{
		if (dta->read[0][2] != 0 || dta->read[1] != 0)
		{
			temp = ft_strtrim(dta->redi[0], " ");
			free (dta->redi[0]);
			//free_double_tab(dta->redi);
			//dta->redi = ft_splitt(dta->exec[0], '>');
			dta->file = open(dta->redi[0], O_TRUNC | O_CREAT | O_WRONLY,
					S_IRUSR | S_IWUSR);
			close(dta->file);
			dta->redi[0] = temp;
			free (temp);
			printf(YELLOW "ICI\n" RESET);
		}
		else
		{
			g_exit_status = 2;
			printf("syntax error near unexpected token `newline'\n");
		}
	}
	else
		check_redirect3(dta);
}

void	check_redirect3(t_data *dta)
{
	if ((ft_strncmpp(&dta->read[0][0], ">", 1) == 0) && dta->read[0][1] == 0)
	{
		if (dta->read[1] != 0)
		{
			if (ft_strncmpp(&dta->read[1][0], ">", 1) == 0)
			{
				g_exit_status = 2;
				printf("%s\n", "syntax error near unexpected token '>'");
				return ;
			}
			dta->redi[0] = ft_strtrim(dta->redi[0], " ");
			dta->file = open(dta->redi[0], O_TRUNC | O_CREAT | O_WRONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			close(dta->file);
		}
		else
		{
			g_exit_status = 2;
			printf("syntax error near unexpected token `newline'\n");
		}
	}
	else
		check_redirect2(dta);
}

void	check_redirect2(t_data *dta)
{
	if ((ft_strncmpp(&dta->read[0][0], ">", 1) == 0) && dta->read[0][1] != 0)
	{
		if (dta->read[0][1] != '>' && dta->read[0][2] != 0)
		{
			dta->file = open(dta->redi[0], O_TRUNC | O_CREAT | O_WRONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			close(dta->file);
		}
		if ((ft_strncmpp(&dta->read[0][1], ">", 1) == 0)
			&& dta->read[0][2] != 0)
		{
			dta->file = open(dta->redi[0], O_TRUNC | O_CREAT | O_WRONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			close(dta->file);
		}
	}
}
