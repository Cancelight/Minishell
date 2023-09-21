/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redirec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:22:28 by bkiziler          #+#    #+#             */
/*   Updated: 2023/09/21 19:57:52 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

int	append_redirection(char *str, int i)
{
	int		fd;
	char	*file;
	int		n;

	while (str[i] == 32)
		i++;
	n = i;
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != 32)
		i++;
	file = substr(str, n, i - n);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		exit_program("Fd Error", -1);
	if (strchar(&str[i], '>') == -1)
		change_data_output(file);
	else
		free(file);
	close(fd);
	return(--i);
}

void	change_data_output(char *file)
{
	if (g_data->output_file)
		free (g_data->output_file);
	g_data->output_file = file;
}
