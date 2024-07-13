/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rredirect_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:09:35 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/13 21:03:40 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	regroup_cmd_args_input(t_data *dta)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strtrim(dta->rredi[1], " ");
	dta->rredi[0] = ft_strtrim(dta->rredi[0], " ");
	while (temp[i] != ' ')
		i++;
	while (temp[i] == ' ')
		i++;
	if (dta->rredi[1])
		free (dta->rredi[1]);
	dta->rredi[1] = ft_strdupp(temp + i);
	if (temp)
		free (temp);
	dta->rredi[0] = ft_strjoin_freee(dta->rredi[0], " ");
	dta->rredi[0] = ft_strjoin_freee(dta->rredi[0], dta->rredi[1]);
}

void	exec_redir_input(t_data *dta, char **envp)
{
	int	incpy;

	incpy = dup(STDIN_FILENO);
	if (access(dta->str[0], F_OK) == -1)
	{
		perror("Error file");
		return ;
	}
	else
		dta->file = open(dta->str[0], O_TRUNC | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dta->cmd1 = ft_splitt(dta->rredi[0], ' ');
	search_path(dta, envp);
	if (access(dta->cmd1[0], X_OK) == -1)
		perror("Command not found ");
	else
	{
		dup2(dta->file, STDIN_FILENO);
		close(dta->file);
		execute_solo(dta->cmd1, dta->envp);
		waitpid(-1, NULL, 0);
		dup2(incpy, STDIN_FILENO);
		close(incpy);
	}
	return ;
}

void	handl_redirect_input2(t_data *dta, char **envp)
{
	if (count_redir(dta->exec[0], '<'))
	{
		dta->rredi = ft_splitt(dta->exec[0], '<');
		dta->str = ft_splitt(dta->rredi[1], ' ');
		if (dta->str[1] != NULL)
			regroup_cmd_args_input(dta);
		exec_redir_input(dta, envp);
	}
}
