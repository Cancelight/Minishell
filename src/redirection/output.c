/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:26:15 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 17:44:00 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

int	output_redirection(char *str, int i)
{
	int		fd;
	char	*file;

	while (str[i] == 32)
		i++;
	file = trim_quote(str, i);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		exit_program("Fd Error aşkımmmmm oputput redirction func daymış buda biliyon mu xd", -1);
	close(fd);
	if (strchar(&str[i], '>') == -1)
		change_data_output(open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777), 0);
	free(file);
	return(--i);
}
