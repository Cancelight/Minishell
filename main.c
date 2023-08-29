/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/29 19:36:11 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

int	main(int argc, char **argv, char **envp)
{
	g_data = malloc(sizeof(t_data) * 1);
	g_data->argc = argc;
	g_data->argv = argv;
	g_data->envp = envp;
	reading_line();
	signal_function();//şimdilik çalışmıyor projenin ana hatları bitince yazılacak
}

void	nav_redirection(t_parse *parse)
{
	heredoc(parse);
}

void	heredoc_list(t_parse *parse)
{
	while (parse != NULL)
	{
		heredoc_list;
	}
}

int	search(char *detect, char *found)
{
	int	i;
	int	a;

	i = -1;
	while(detect[++i])
	{
		while (detect[i] && found[a] && detect[i] == found[a])
		{
			i++;
			a++;
		}
		if (found[a] == '\0')
			return (1);
		else if (a > 0)
			a = 0;
	}
	return(0);
}
