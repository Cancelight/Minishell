/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/09/20 13:26:10 by bkiziler         ###   ########.fr       */
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
	g_data->parse = NULL;
	reading_line();
	signal_function();//şimdilik çalışmıyor projenin ana hatları bitince yazılacak
}

void	nav_redirection(t_parse *parse)
{
	int	i;

	heredoc_list(parse);
	while (parse != NULL)
	{
		i = -1;
		while(parse->content[++i])
		{
			if (parse->content[i] == '\'')
				i = strchar(&parse->content[++i], '\'') + 1;
			else if (parse->content[i] == '"')
				i = strchar(&parse->content[++i], '"') + 1;
			else if (parse->content[i] == '<')
				i = input_redirection(parse->content, ++i);
			else if (parse->content[i] == '>' && parse->content[i + 1] == '>')
				i = append_redirection(parse->content, i + 2);
			else if (parse->content[i] == '>' && parse->content[i + 1] != '>')
				i = output_redirection(parse->content, ++i);
		}
		if (strrchar(parse->content, '<') != 0 && \
			parse->content[strrchar(parse->content, '<') - 1] == '<') //tüm content döndükten sonra en sondaki '<' sembol appendse inputu dğeiştiriyor
			change_data_input("heredoc");
		parse = parse->next;
	}
}


