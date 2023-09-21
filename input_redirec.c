/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:37:34 by bkiziler          #+#    #+#             */
/*   Updated: 2023/09/21 19:08:27 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

int	input_redirection(char *str, int i)
{
	int		n;
	char	*file;
	int		fd;

	if (str[i] == '<')
		return (i + 1);
	while (str[i] == 32)
		i++;
	n = i;
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != 32)
		i++;
	file = substr(str, n, i - n);
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit_program("No such file or directory", -1);
	if (strchar(&str[i], '<') == -1)
		change_data_input(file);
	else
		free(file);
	close(fd);
	return (--i);
}
