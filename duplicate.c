/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:06:10 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/02 10:02:59 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

void	duplication(char *input, char *output)
{
	static int	change = 0;
	int			fd_in;
	int			fd_out;
	int			std_in;
	int			std_out;

	if (change == 0)
	{
		std_in = dup(0);
		std_out = dup(1);
		change = 1;
	}
	if (input != NULL)
	{
		fd_in = open(input, O_RDONLY | O_APPEND, 0777);
		dup2(fd_in, 0);
		if (dup2(fd_in, 0) < 0)
			exit_program("Fd Error.", -1);
		close(fd_in);
	}
	else
	{
		if (dup2(std_in, 0) < 0)
			exit_program("Fd Error.", -1);
	}
	if (output != NULL)
	{
		if (g_data->append_flag)
			fd_out = open(output, O_WRONLY | O_APPEND, 0777);
		else
			fd_out = open(output, O_WRONLY | O_APPEND, 0777);//direkt silip yazması için flag gerekiyor
		dup2(fd_out, 1);
		if (dup2(fd_out, 1); < 0)
			exit_program("Fd Error.", -1);
		close(fd_out);
	}
	else
	{
		if (dup2(std_out, 1) < 0)
			exit_program("Fd Error.", -1);
	}
}
