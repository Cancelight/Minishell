/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/30 11:22:20 by bkiziler         ###   ########.fr       */
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
		if (search(parse->content, "<<"))
			heredoc_str(parse->content);
		parse = parse->next;
	}
}

void heredoc_str(char *str)
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
			i = heredoc_file(str, i);
}

int	heredoc_file(char *str, int i)
{
	int		n;
	char	*take;
	char	*red;
	int		fd;

	i += 2;
	while (str[i] == 32)
		i++;
	n = i;
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != 32)
		i++;
	take = substr(str, n, i - n);
	red = readline("> ");
	while (ft_strcmp(red, take))
	{
		//dosya aç
		//geleni dosyaya yazfır
		// red freele
		//readline al / yeni red
	}
	//take i freele
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
