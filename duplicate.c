/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:06:10 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/03 16:31:16 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

static void	input_duplication(int	fd_in)
{
	if (dup2(fd_in, 0) < 0)
		exit_program("Fd Error.", -1);
	close(fd_in);

}

static void	output_duplication(int	fd_out)
{
	if (dup2(fd_out, 1) < 0)
		exit_program("Fd Error.", -1);
	close(fd_out);
}

void	duplication(int	fd_in, int	fd_out)
{
	static int	change = 0;
	int			std_in;
	int			std_out;

	if (change == 0)
	{
		std_in = dup(0);
		std_out = dup(1);
		change = 1;
	}
	if (fd_in >= 0)
		input_duplication(fd_in);
	else
	{
		if (dup2(std_in, 0) < 0)
			exit_program("Fd Error.", -1);
	}
	if (fd_out >= 0)
		output_duplication(fd_out);
	else
	{
		if (dup2(std_out, 1) < 0)
			exit_program("Fd Error.", -1);
	}
	write(0, "heyy", 5);
	write(1, "dude", 5);
}
