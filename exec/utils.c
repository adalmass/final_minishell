/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:59 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 19:37:01 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom(void)
{
	printf("\033[0;36m");
	printf("  __  __ _       _  _____ _          _ _  \n");
	printf(" |  \\/  (_)     (_)/ ____| |        | | | \n");
	printf(" | \\  / |_ _ __  _| (___ | |__   ___| | | \n");
	printf("\033[0;34m");
	printf(" | |\\/| | | '_ \\| |\\___ \\| '_ \\ / _ \\ | | \n");
	printf("\033[0;35m");
	printf(" | |  | | | | | | |____) | | | |  __/ | | \n");
	printf(" |_|  |_|_|_| |_|_|_____/|_| |_|\\___|_|_| \n");
	printf("                                          \n");
}

char	*ft_strjoin_freee(char *stock, char *temp)
{
	char	*memory;
	int		i;
	int		j;

	memory = malloc(sizeof(char) * (ft_strlenn(stock) + ft_strlenn(temp) + 1));
	if (!memory)
	{
		free(stock);
		return (NULL);
	}
	i = -1;
	while (stock[++i])
		memory[i] = stock[i];
	memory[i] = '\0';
	j = i;
	i = -1;
	while (temp[++i])
		memory[j + i] = temp[i];
	memory[j + i] = '\0';
	free(stock);
	return (memory);
}

char	*ft_strjoin_space(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;
	char	*str;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	n = 0;
	i = 0;
	str = malloc(sizeof(char) * (ft_strlenn(s1) + ft_strlenn(s2)) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = ' ';
	i++;
	while (s2[n++])
		str[i + n] = s2[n];
	str[i + n] = 0;
	return (str);
}

void	handl_prompt(void)
{
	signal(SIGINT, handl_signals);
	signal(SIGQUIT, handl_signals);
}
