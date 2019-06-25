/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonzale <bgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:28:29 by bgonzale          #+#    #+#             */
/*   Updated: 2019/06/24 17:02:14 by bgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	j;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		j = 0;
		while (*(haystack + j) == *(needle + j))
		{
			if (!*(needle + j + 1))
				return ((char *)haystack);
			j++;
		}
		haystack++;
	}
	return (0);
}

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
	char			*route;
	char *path;
	struct stat sb;
	struct passwd *pwd;
	struct group	*grp;
	char *curtime;

	if (!(dir = opendir(name)))
	{
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		route = ft_routecat(name, entry->d_name, route);
		lstat(route, &sb);
		pwd = getpwuid(sb.st_uid);
		grp = getgrgid(sb.st_gid);
		curtime = ctime(&sb.st_mtimespec.tv_sec);
		//Permisions
		printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
		printf((sb.st_mode & S_IRUSR) ? "r" : "-");
		printf((sb.st_mode & S_IWUSR) ? "w" : "-");
		printf((sb.st_mode & S_IXUSR) ? "x" : "-");
		printf((sb.st_mode & S_IRGRP) ? "r" : "-");
		printf((sb.st_mode & S_IWGRP) ? "w" : "-");
		printf((sb.st_mode & S_IXGRP) ? "x" : "-");
		printf((sb.st_mode & S_IROTH) ? "r" : "-");
		printf((sb.st_mode & S_IWOTH) ? "w" : "-");
		printf((sb.st_mode & S_IXOTH) ? "x" : "-");
		printf(" %2d ", sb.st_nlink);
		printf("%1s", pwd->pw_name);
		printf("%11s", grp->gr_name);
		printf("%9lld", sb.st_size);
		if (ft_strstr(curtime, "2019"))
		{
			printf("%7.6s %.5s", (curtime + 4), (curtime + 11));
		}
		else
		{
			printf("%7.6s %5.4s", (curtime + 4), (curtime + 20));
		}
		if (S_ISDIR(sb.st_mode))
		{
			if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
			{
				printf("%*s[%s]\n", indent, "", entry->d_name);
				continue;
			}
			path = ft_routecat(name, entry->d_name, path);
			printf("%*s[%s]\n", indent, "", entry->d_name);
			listdir(path, indent + 2);
		}
		else
		{
			printf("%*s %s\n", indent, "", entry->d_name);
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
