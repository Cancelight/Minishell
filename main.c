/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/09/21 19:11:45 by bkiziler         ###   ########.fr       */
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
		while (parse->content[++i])
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
		printf("original content: %s\n", parse->content);
		if (strrchar(parse->content, '<') != 0 && \
			parse->content[strrchar(parse->content, '<') - 1] == '<') //tüm content döndükten sonra en sondaki '<' sembol appendse inputu dğeiştiriyor
			change_data_input(str_dup("heredoc"));
		printf("aa\n");
		parse->content = remove_redirection(parse->content, NULL);
		printf("silinmiş content: %s\n", parse->content);
		parse = parse->next;
	}
	printf("input: %s, output: %s\n", g_data->input_file, g_data->output_file);
}

//ls -a >>b grep -v | ls -l

char	*remove_redirection(char *str, char *new)
{
	int		i;
	int		n;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == 32)
			i++;
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] == 32 || str[i] == '<' || str[i] == '>')
				i++;
			while (str[i] && str[i] != 32)
				i++;
		}
		else
		{
			n = i;
			while (str[i] && str[i] != '<' && str[i] != '>')
				i++;
			new = s2_strjoin(new, substr(str, n, i - n));
		}
	}
	free(str);
	return (new);
}
