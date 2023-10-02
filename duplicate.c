/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:06:10 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/02 11:09:01 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*g_data;

static void	input_duplication(char *input)
{
	int	fd_in;

	fd_in = open(input, O_RDWR | O_APPEND);
	if (dup2(fd_in, 0) < 0)
		exit_program("Fd Error.", -1);
	close(fd_in);
}

static void	output_duplication(char *output)
{
	int	fd_out;

	if (g_data->append_flag)
		fd_out = open(output, O_RDWR | O_APPEND);
	else
		fd_out = open(output, O_RDWR | O_APPEND | O_TRUNC);//direkt silip yazması için flag gerekiyor
	if (dup2(fd_out, 1) < 0)
		exit_program("Fd Error.", -1);
	close(fd_out);
}

void	duplication(char *input, char *output)
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
	if (input != NULL)
		input_duplication(input);
	else
	{
		if (dup2(std_in, 0) < 0)
			exit_program("Fd Error.", -1);
	}
	if (output != NULL)
		output_duplication(output);
	else
	{
		if (dup2(std_out, 1) < 0)
			exit_program("Fd Error.", -1);
	}
	write(0, "heyy", 5);
	write(1, "dude", 5);
}
