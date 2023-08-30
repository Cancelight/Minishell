/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/30 16:27:18 by bkiziler         ###   ########.fr       */
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
	int	i;

	heredoc_list(parse);
	while (parse != NULL)
	{
		i = -1;
		while(parse->content[++i])
		{
			if (str[i] == '\'')
				i = strchar(&str[++i], '\'') + 1;
			else if (str[i] == '"')
				i = strchar(&str[++i], '"') + 1;
			else if (parse->content[i] == '<' && parse->content[i] != '<')
				i = input_redirection(parse->content, i);
			else if (parse->content[i] == '>' && parse->content[i] == '>')
				i = append_redirection(parse->content, i);
			else if (parse->content[i] == '>' && parse->content[i] != '>')
				i = output_redirection(parse->content, i);
		}
		parse = parse->next;
	}
}

int	input_redirection(char *str, int i)
{

}

/* her heredoc için readline al bu readlineları bir fdye at aynı fd üzerine flag ile yaz fd için sıfırdan yazma flagi var onu bul
		heredocın sonuncusunu genel structta olan input dosyasına at
		input redirectionına geldiğinde ('<') son inputtan sonra heredoc olup olmadığına bak eğer yoksa structtaki input dosyasını değiştir kullanılmasa bile dosya açmayı unutma */
