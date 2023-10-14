/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:29:28 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 18:04:40 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

t_data	*g_data;

void	exit_program(char *str, int i)//düzeltilmesi lazım
{
	write(2, str, strlen(str));
	write(2, "\n", 1);
	exit(i);
}

void	clear_lst(t_parse **lst)
{
	t_parse *cnext;

	cnext = (*lst);
	while (cnext != (NULL))
	{
		cnext = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		(*lst) = cnext;
	}
}

void	reset_struct(void)
{
	g_data->input_file = -2;
	g_data->output_file = -2;
	g_data->heredoc_cnt = 0;
	g_data->syntax_flag = 0;
	g_data->dbl = 0;
	g_data->sng = 0;
	g_data->line = NULL;
	g_data->parse = NULL;
}

void	re_free(void)
{
	if (!(g_data->sng % 2) && !(g_data->dbl % 2))
		free(g_data->line);
	clear_lst(&(g_data->parse));
	reset_struct();
}

void	free_command_db(char **command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	while (command[i] != 0)
	{
		free(command[i]);
		i++;
	}
	free(command);
}
