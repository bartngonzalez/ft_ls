/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonzale <bgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:28:29 by bgonzale          #+#    #+#             */
/*   Updated: 2019/06/21 01:24:00 by bgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	int i;
	int i_test;
	int num_arg;
	t_flags *ptrflags;
	DIR *dir;
	struct dirent *sd;

	i = 1;
	i_test = 1;
	num_arg = argc - 1;
	ptrflags = (t_flags *)malloc(sizeof(t_flags));

	// TSTING
	printf("argc = [%d]\n", argc);
	printf("num_arg = [%d]\n", num_arg);
	while (i_test <= num_arg)
	{
		printf("argv[%d] = [%s]\n", i_test, argv[i_test]);
		i_test++;
	}

	// set all flags to 0
	ptrflags->R = 0;
	ptrflags->l = 0;
	ptrflags->a = 0;
	ptrflags->r = 0;
	ptrflags->t = 0;

	// if the argc > 1 && first argument has [-] every argument after it is
	// considered a flag only if it starts with [-]
	if (argc > 1 && argv[1][0] == '-')
	{
		int k = 1;
		while (argv[i][0] == '-')
		{
			// iterate through each arguments string and set flags R, l, a, r, t
			while (argv[i][k] != '\0')
			{
				// TESTING
				// printf("argv[i][k] = [%c]\n", argv[i][k]);
				if (argv[i][k] == 'R')
					ptrflags->R = 1;
				else if (argv[i][k] == 'l')
					ptrflags->l = 1;
				else if (argv[i][k] == 'a')
					ptrflags->a = 1;
				else if (argv[i][k] == 'r')
					ptrflags->r = 1;
				else if (argv[i][k] == 't')
					ptrflags->t = 1;
				else
				{
					printf("ft_ls: illegal option -- %c\n", argv[i][k]);
					printf("usage: ./ft_ls [-Rlart] [file ...]\n");
					exit(1);
				}
				k++;
			}
			k = 1;
			i++;
			if (i == argc)
				break ;
		}
	}
	printf("R = [%d]\n", ptrflags->R);
	printf("l = [%d]\n", ptrflags->l);
	printf("a = [%d]\n", ptrflags->a);
	printf("r = [%d]\n", ptrflags->r);
	printf("t = [%d]\n", ptrflags->t);

	// find files or directory names and save them
	if (argc > 1)
	{
		while (i <= num_arg)
		{
			// printf("*** %d\n", i);
			// printf("%s\n", argv[i]);
			dir = opendir(argv[i]);
			if (dir == NULL)
			{
				printf("ls: %s: No such file or directory\n", argv[i]);
			}
			else
			{
				while ((sd = readdir(dir)) != NULL)
				{
					printf(">> [%s]\n", sd->d_name);
				}
				closedir(dir);
			}
			i++;
		}
	}
	return (0);
}
