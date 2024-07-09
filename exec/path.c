/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:43 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/09 20:31:31 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_path(t_data *dta)
{
	int		i;
	char	*path;

	i = 0;
	while (dta->envp[i])
	{
		if (ft_strncmpp(dta->envp[i], "PATH=", 5) == 0)
			dta->path = ft_splitt(dta->envp[i] + 5, ':');
		i++;
	}
	i = 0;
	if (access(dta->cmd1[0], X_OK) == 0)
		return ;
	while (dta->path[i])
	{
		path = ft_strjoin(dta->path[i], "/");
		path = ft_strjoin(path, dta->cmd1[0]);
		if (access(path, X_OK) == 0)
			break ;
		i++;
	}
	free(dta->cmd1[0]);
	dta->cmd1[0] = ft_strdupp(path);
}
