/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:03:01 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/09 16:44:04 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(t_data *dta, int cmd)
{
	int	y;
	int	len_read;

	y = 0;
	len_read = 0;
	while (dta->read[cmd][len_read] && dta->read[cmd][len_read] != '=')
		len_read++;
	while (dta->cpy_envp[y])
	{
		if (ft_strncmpp(dta->cpy_envp[y], dta->read[cmd], len_read) == 0)
		{
			if (dta->read[cmd][len_read] == '\0')
				return (1);
			free (dta->cpy_envp[y]);
			dta->cpy_envp[y] = ft_strdupp(dta->read[cmd]);
			return (1);
		}
		y++;
	}
	return (0);
}
