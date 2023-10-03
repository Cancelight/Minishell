/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:26:15 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/02 11:43:22 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

int	output_redirection(char *str, int i)
{
	int		fd;
	char	*file;

	while (str[i] == 32)
		i++;
	file = trim_quote(str, i);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		exit_program("Fd Error", -1);
	if (strchar(&str[i], '>') == -1)
		change_data_output(fd, 0);
	free(file);
	return(--i);
}
