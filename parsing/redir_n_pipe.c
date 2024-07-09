/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_n_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:48:46 by aldalmas          #+#    #+#             */
/*   Updated: 2024/03/29 10:09:45 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	redir_left_found(t_parse *p, char next_char)
{
	p->redir_l_count++;
	check_all_errors(p);
	if (next_char != '<')
		p->redir_l_count = 0;
}

void	redir_right_found(t_parse *p, char next_char)
{
	if (next_char == '<')
		parse_error(p, RED "syntax error with `<'" RESET);
	p->redir_r_count++;
	check_all_errors(p);
	if (next_char != '>')
		p->redir_r_count = 0;
}

void	first_check_cmdline(t_parse *p)
{
	int	i;

	i = 0;
	while (p->cmd_line[i])
	{
		if (p->cmd_line[i] == '>')
			redir_right_found(p, p->cmd_line[i + 1]);
		if (p->cmd_line[i] == '<')
			redir_left_found(p, p->cmd_line[i + 1]);
		if (p->cmd_line[i] == '|')
			pipe_found(p, p->cmd_line[i + 1]);
		i++;
	}
}
