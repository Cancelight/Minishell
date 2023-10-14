/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:15:08 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 17:42:51 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

void	heredoc_list(t_parse *parse)
{
	while (parse != NULL)
	{
		if (search(parse->content, "<<") && g_data->heredoc_cnt > 0)
			heredoc_str(parse->content);
		parse = parse->next;
	}
}

void	heredoc_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && g_data->heredoc_cnt > 0)
	{
		if (str[i] == '\'')
			i += strchar(&str[i + 1], '\'') + 2;
		else if (str[i] == '"')
			i += strchar(&str[i + 1], '"') + 2;
		else if (str[i] == '<' && str[i + 1] == '<')
			i = heredoc_file(str, i + 2) - 1;
	}
}

int	heredoc_file(char *str, int i)
{
	char	*check;
	char	*take;
	int		fd;

	while (str[i] == 32)
		i++;
	check = trim_quote(str, i);
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	take = readline("> ");
	while (ft_strcmp(take, check))
	{
		ft_putendl_fd(take, fd);
		free(take);
		take = readline("> ");
	}
	free(take);
	free(check);
	close(fd);
	change_data_input(open("heredoc", O_RDWR | O_TRUNC, 0777));
	g_data->heredoc_cnt--;
	return (i);
}

void	change_data_input(int file)
{
	if (g_data->input_file == -1 || file == -1)
		exit_program("Fd Error change data input aşkım bunlar ne böyle ", -1);
	if (g_data->input_file >= 0)
		close(file);
	g_data->input_file = file;
}
