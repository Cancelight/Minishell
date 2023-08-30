/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/30 14:57:39 by bkiziler         ###   ########.fr       */
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
	heredoc_list(parse);
}

void	heredoc_list(t_parse *parse)
{
	while (parse != NULL)
	{
		if (search(parse->content, "<<"))
			heredoc_str(parse->content);
		parse = parse->next;
	}
}

void	heredoc_str(char *str)
{
	int	i;

	i = -1;
	while(str[++i])
	{
		if (str[i] == '\'')
			i = strchar(&str[++i], '\'') + 1;
		else if (str[i] == '"')
			i = strchar(&str[++i], '"') + 1;
		else if (str[i] == '<' && str[i + 1] == '<')
			i = heredoc_file(str, i + 2) - 1;
	}
}

int	heredoc_file(char *str, int i)
{
	int		n;
	char	*check;
	char	*take;
	int		fd;

	while (str[i] == 32)
		i++;
	n = i;
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != 32)
		i++;
	check = substr(str, n, i - n);
	fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	take = readline("> ");
	while (ft_strcmp(take, check))
	{
		ft_putendl_fd(take, fd);
		free(take);
		take = readline("> ");
	}
	free(take);
	free(check);
	close(fd);//close fd yapmalı mıyım
	change_data_input(str_dup("heredoc"));
	return (i);
}

void	change_data_input(char *file)
{
	if (g_data->input_file)
		free (g_data->input_file);
	g_data->input_file = file;
}

/* her heredoc için readline al bu readlineları bir fdye at aynı fd üzerine flag ile yaz fd için sıfırdan yazma flagi var onu bul
		heredocın sonuncusunu genel structta olan input dosyasına at
		input redirectionına geldiğinde ('<') son inputtan sonra heredoc olup olmadığına bak eğer yoksa structtaki input dosyasını değiştir kullanılmasa bile dosya açmayı unutma */

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
