/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/01 20:51:52 by bkiziler         ###   ########.fr       */
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
	g_data->append_flag = -1;
	g_data->input_file = NULL;
	g_data->output_file = NULL;
	g_data->line = NULL;
	g_data->parse = NULL;
	reading_line();
	signal_function();//şimdilik çalışmıyor proje bitince yazılacak
}

char	**nav_redirection(char *content)
{
	int	i;

	i = -1;
	while (content[++i] )
	{
		if (content[i] == '\'')
			i += strchar(&content[i + 1], '\'') + 2;
		else if (content[i] == '"')
			i += strchar(&content[i + 1], '"') + 2;
		else if (content[i] == '<')
			i = input_redirection(content, ++i);
		else if (content[i] == '>' && content[i + 1] == '>')
			i = append_redirection(content, i + 2);
		else if (content[i] == '>' && content[i + 1] != '>')
			i = output_redirection(content, ++i);
	}
	if (strrchar(content, '<') != 0 && \
		content[strrchar(content, '<') - 1] == '<') //tüm content döndükten sonra en sondaki '<' sembol heredocsa inputu dğeiştiriyor
		change_data_input(str_dup("heredoc"));
	content = remove_redirection(content, NULL);
	return (libft_split(content, 32));
}

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
		else if (str[i])
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
