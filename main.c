/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/30 17:53:31 by bkiziler         ###   ########.fr       */
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
			if (parse->content[i] == '\'')
				i = strchar(&parse->content[++i], '\'') + 1;
			else if (parse->content[i] == '"')
				i = strchar(&parse->content[++i], '"') + 1;
			else if (parse->content[i] == '<' && parse->content[i + 1] != '<')
				i = input_redirection(parse->content, ++i);
			/*else if (parse->content[i] == '>' && parse->content[i + 1] == '>')
				i = append_redirection(parse->content, i + 2);
			else if (parse->content[i] == '>' && parse->content[i + 1] != '>')
				i = output_redirection(parse->content, ++i);*/
		}
		if (strrchar(parse->content, '<') != 0 && \
			parse->content[strrchar(parse->content, '<') - 1] == '<')
			change_data_input("heredoc");
		parse = parse->next;
		printf("input file = %s\n", g_data->input_file);
	}
}

int	input_redirection(char *str, int i)
{
	int	n;
	char *file;
	int	fd;

	while (str[i] == 32)
		i++;
	n = i;
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != 32)
		i++;
	file = substr(str, n, i - n);
	printf("file:%s\n", str + i);
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit_program("No such file or directory", -1);
	if (strchar(&str[i], '<') == -1)
		change_data_input(file);
	close(fd);
	printf("str:%s\n", str);
	return (--i);
}

/* her heredoc için readline al bu readlineları bir fdye at aynı fd üzerine flag ile yaz fd için sıfırdan yazma flagi var onu bul
		heredocın sonuncusunu genel structta olan input dosyasına at
		input redirectionına geldiğinde ('<') son inputtan sonra heredoc olup olmadığına bak eğer yoksa structtaki input dosyasını değiştir kullanılmasa bile dosya açmayı unutma */
