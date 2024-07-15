/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:38:26 by aldalmas          #+#    #+#             */
/*   Updated: 2024/03/29 11:39:13 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_all_errors(t_parse *p)
{
	error_redirection(p);
	error_pipe(p);
}

void	error_redirection(t_parse *p)
{
	if (p->redir_l_count > 3)
		parse_error(p, RED "syntax error with `<'" RESET);
	if (p->redir_r_count > 2)
		parse_error(p, RED "syntax error with `>'" RESET);
}

int	error_pipe(t_parse *p)
{
	if (p->pipe_count > 2)
	{
		parse_error(p, RED "syntax error with `|'" RESET);
		return (1);
	}
	else if (p->pipe_count == 2)
	{
		parse_error(p, YELLOW "(no bonus) syntax with `||'" RESET);
		return (1);
	}
	return (0);
}

void	redir_last_char(t_parse *p, char *cmd)
{
	int	i;

	i = ft_strlen(cmd) - 1;
	while (i > 0)
	{
		if (ft_isalpha(cmd[i]))
			return ;
		if (cmd[i] == '<' || cmd[i] == '>')
			parse_error(p, RED "syntax error with `newline'");
		i--;
	}
}
