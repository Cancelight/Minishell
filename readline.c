/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/04 21:23:40 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data *g_data;

void	reading_line(void)
{
	while (1)
	{
		g_data->line = readline("minishelli > ");
		if (g_data->line && *(g_data->line))
		{
			add_history(g_data->line);
			parser();
			syntax_check(g_data->parse);
			//continue öncesinde freeleme fonksiyonlarını çağırıp error yazdırman lazım syntax flag = 0 olmalı  heredoc count = 0
			if(g_data->syntax_flag == 1 && g_data->heredoc_cnt == 0){
				printf("error var canım cigerim\n");
				continue;
			}
			heredoc_list(g_data->parse);
			if(g_data->syntax_flag == 1){
				printf("error var canım cigerim\n");
				continue;
			}
			// node içeriğine git include'dan bak -Alp
			//Bağlı listenin yapısı örnek commandline = "ls << a | grep a"
			//node 1 = ls << a ->next node2
			//node 2 = | ->next node 3
			//node 3 = grep a->next'i null bunu biliyorsun demi ali -Alp
			//parserdan böyle çıkıyor ve sonra heredoc filan çalışıyor
			//burdan sonra sen napiyon biliyon mu akrabam benim
			//while içinde pipe geldiğinde geçerek contenti alıp nav_redirection'a gönderirsen contenti
			//sana double array dönücek execve ye gönderebileceğin.
			//ayrıyeten her nav_redirectiondan return aldığında structta nav_redirectiona gönderilen son komut line'ın
			//input ve output dosyalarının isimleri  structtan (g_data->input_file ve g_data->output_file) alınıp işlenebilir
			//outputta append olup olmadığını belirtmek için append_flag vardır, kullanılmadığında -1,
			//append_redirection varsa 1, append redirection yoksa 0 değerlerini alır.
			//alınan dosyaları değiştirmek için dup2 fonksiyonunu şudur:

			//redirectionı kaldırılmış ve double arraye çevirilmiş halidir kullanım while örneği:
			//(parse exec kısmı bittikten sonra freeleniyor, free yazmana gerek yok).
			char **command;

			command = nav_redirection(g_data->parse->content);
			system("leaks minishell");
			printf("mainde content : %s\n",g_data->parse->content);
			int i = 0;
/*			while(command[i] != 0){
				printf("aşkım %s\n",command[i]);
				i++;
			}*/
			/*while(temp != NULL){
				printf("main content : %s\n",temp->content);
				temp = temp->next;
			}*/
			//clear_lst(&(g_data->parse));
			printf("heyy\n");
		}
	}
}

			/*while (temp != NULL)
			{
				int	fd_out;
				int	fd_in;
				char **command_line = NULL;
				if (temp->content[0] != '|') //pipelar direkt atlanabilir
				{
					command_line = nav_redirection(temp->content);
				//system("leaks minishell");
					fd_out = g_data->output_file;//bunları yeniden atmak yerine fonksiyona atabilirsin sadece daha net görünsün diye variable'a attım
					fd_in = g_data->input_file;
					//duplication(fd_in, fd_out);
				}
				temp =temp->next;
			}
			temp = g_data->parse;
			g_data->input_file = -2;//-2 olma sebepleri halihazırda atanmış dosya bulunmuyor Null gibi düşün
			g_data->output_file = -2;
			//duplication(g_data->input_file, g_data->output_file);
			//buradan itibaren execten sonra çalışacak genel freeleme ve yeni komut line alma işlemi süreci başlıyor
			if (!(g_data->sng % 2) && !(g_data->dbl % 2))
				free(g_data->line);

			while(temp != NULL){
				printf("maindeki content : %s\n",g_data->parse->content);
				temp = temp->next;
			}*/
