/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:24:55 by aldalmas          #+#    #+#             */
/*   Updated: 2024/03/29 14:46:12 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_error(t_parse *p, char *error_msg)
{
	if (p->error_found == 0)
		p->error_found = 1;
	else
		return ;
	g_exit_status = 2;
	ft_putstr_fd(RED "minishell: " RESET, 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	init_struct(p);
}

void	init_struct(t_parse *p)
{
	p->count = 0;
	p->space_found = 0;
	p->echo_found = 0;
	p->idx_start_quote = 0;
	p->idx_end_quote = 0;
	p->len_cmd_line = 0;
	p->pipe_number = 0;
	p->space_number = 0;
	p->pipe_count = 0;
	p->redir_l_count = 0;
	p->redir_r_count = 0;
	p->cmdtab_redir_l = 0;
	p->cmdtab_redir_r = 0;
	p->sub_start = 0;
	p->sub_end = 0;
}

void	free_double_tab(char **tab)
{
	int	y;

	y = 0;
	if (tab)
	{
		while (tab[y] != NULL)
		{
			if (tab[y])
			{
				free (tab[y]);
				tab[y] = NULL;
			}
			y++;
		}
		free (tab);
		tab = NULL;
	}
}

char	*trim_quotes(char *splitted_built, char quote)
{
	int		i;
	int		j;
	char	*str_trim;

	i = 0;
	j = 0;
	str_trim = malloc(sizeof(char) * (ft_strlen(splitted_built) - 2) + 1);
	while (splitted_built[i])
	{
		if (splitted_built[i] != quote)
		{
			str_trim[j] = splitted_built[i];
			j++;
		}
		i++;
	}
	str_trim[j] = '\0';
	free (splitted_built);
	return (str_trim);
}
