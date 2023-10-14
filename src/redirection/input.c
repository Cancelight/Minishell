/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:37:34 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 17:43:55 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

int	input_redirection(char *str, int i)
{
	char	*file;
	int		fd;

	if (str[i] == '<')
		return (i + 1);
	while (str[i] == 32)
		i++;
	file = trim_quote(str, i);
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit_program("No such file or directory", -1);
	if (strchar(&str[i], '<') == -1)
		change_data_input(fd);
	free(file);
	return (--i);
}
