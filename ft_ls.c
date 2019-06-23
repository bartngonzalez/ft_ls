/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonzale <bgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:28:29 by bgonzale          #+#    #+#             */
/*   Updated: 2019/06/22 17:22:17 by bgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_routecat(char *s1, char *s2, char *ptr)
{
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	len = -1;
	while (s1[++len])
		ptr[len] = s1[len];
	ptr[len++] = '/';
	while (*s2)
		ptr[len++] = *s2++;
	ptr[len] = '\0';
	return (ptr);
}

void listdir(char *name, int indent)
{
	DIR *dir;
	struct dirent *entry;
	struct stat sb;
	char			*route;
	char *path;

	if (!(dir = opendir(name)))
	{
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		route = ft_routecat(name, entry->d_name, route);
		lstat(route, &sb);
		if (S_ISDIR(sb.st_mode))
		{
			// printf("*** OK ***\n");
			// char path[1024];
			if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
			{
				printf("%*s[%s]\n", indent, "", entry->d_name);
				continue;
			}
			// snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
			path = ft_routecat(name, entry->d_name, path);
			printf("%*s[%s]\n", indent, "", entry->d_name);
			listdir(path, indent + 2);
		}
		else
		{
			// printf("*** SHIT ***\n");
			printf("%*s- %s\n", indent, "", entry->d_name);
		}
	}
	closedir(dir);
}

int main(int argc, char **argv)
{
	int i;
	int i_test;
	int num_arg;
	t_flags *ptrflags;

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

	// Recursion
	if (argc > 1)
	{
		while (i <= num_arg)
		{
			listdir(argv[i], 0);
			i++;
		}
	}
	return (0);
}
