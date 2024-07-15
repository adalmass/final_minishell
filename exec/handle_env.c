/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:39:37 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 15:39:45 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handl_env(t_data *dta, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	dta->cpy_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		dta->cpy_envp[i] = ft_strdupp(envp[i]);
		i++;
	}
	dta->cpy_envp[i] = NULL;
}
