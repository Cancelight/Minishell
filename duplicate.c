/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:06:10 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/01 20:19:04 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

void	duplication(char *input, char *output)
{
	int	fd_in;
	int	fd_out;

	if (input != NULL)
	{
		fd_in = open(input, O_RDONLY, 0777);
		fd_in = dup2(0, fd_in);
		if (fd_in < 0)
			exit_program("Fd Error.", -1);
	}
	if (output != NULL)
	{
		if (g_data->append_flag)
			fd_out = open(output, O_WRONLY | O_APPEND, 0777);
		else
			fd_out = open(output, O_WRONLY, 0777);
		fd_out = dup2(1, fd_out);
		if (fd_out < 0)
			exit_program("Fd Error.", -1);
	}
}
