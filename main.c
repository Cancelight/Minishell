/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/04 21:24:11 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

char	*ft_strdup(const char *s1)
{
	char	*cp;
	int i = 0;
	cp = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (cp == NULL)
		return (0);
	while(s1[i]){
		cp[i] = s1[i];
		i++;
	}
	return (cp);
}

int	main(int argc, char **argv, char **envp)
{
	g_data = malloc(sizeof(t_data) * 1);
	g_data->argc = argc;
	g_data->argv = argv;
	g_data->envp = envp;
	g_data->append_flag = -1;
	g_data->input_file = -2;
	g_data->output_file = -2;
	g_data->heredoc_cnt = 0;
	g_data->line = NULL;
	g_data->parse = NULL;
	reading_line();
	signal_function();//şimdilik çalışmıyor proje bitince yazılacak
}

char	**nav_redirection(char *content)
{
	int	i;
	char **return_array;
	char *alp;

	alp = ft_strdup(content);
	i = -1;
	while (alp[++i] )
	{
		if (alp[i] == '\'')
			i += strchar(&alp[i + 1], '\'') + 2;
		else if (alp[i] == '"')
			i += strchar(&alp[i + 1], '"') + 2;
		else if (alp[i] == '<')
			i = input_redirection(alp, ++i);
		else if (alp[i] == '>' && alp[i + 1] == '>')
			i = append_redirection(alp, i + 2);
		else if (alp[i] == '>' && alp[i + 1] != '>')
			i = output_redirection(alp, ++i);
	}
	if (strrchar(alp, '<') != 0 && \
		alp[strrchar(alp, '<') - 1] == '<') //tüm content döndükten sonra en sondaki '<' sembol heredocsa inputu dğeiştiriyor
		change_data_input(open("heredoc", O_RDWR | O_TRUNC, 0777));
	alp = remove_redirection(alp, 0);
	return_array = libft_split(alp, 32);
	free(alp);
	return (return_array);
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
