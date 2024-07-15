/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:24:45 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 16:30:43 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_multi_rredir(t_data *dta)
{
	int		j;
	int		len;
	char	*temp;

	j = 0;
	len = 0;
	while (dta->exec[dta->idx][len])
		len++;
	while (j < len)
	{
		if (dta->exec[dta->idx][j] == '<')
		{
			temp = ft_strtrim(dta->rredi[1], " ");
			free (dta->rredi[1]);
			dta->rredi[1] = temp;
			dta->file = open(dta->rredi[1], O_TRUNC | O_WRONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			free (temp);
			return (1);
		}
		j++;
	}
	return (0);
}

void	multi_pipe(t_data *dta, char **envp)
{
	int	in_fd;
	int	out_fd;

	in_fd = STDIN_FILENO;
	dta->idx = 0;
	in_fd = dup(STDIN_FILENO);
	out_fd = dup(STDOUT_FILENO);
	close(dta->file);
	handl_multi_pipe(dta, envp, in_fd);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	while (waitpid(-1, NULL, 0) > 0)
		;
	close(out_fd);
	dta->idx = 0;
	dta->nb_pipe = 0;
}
