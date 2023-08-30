/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:15:08 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/30 19:00:00 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

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
	while (str[++i])
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
		//free(take);
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
