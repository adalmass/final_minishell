/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:55 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/08 22:10:44 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../parsing/parsing.h"

void	handl_signals(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return ;
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return ;
	}
}
