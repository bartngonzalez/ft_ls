/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_boost.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonzale <bgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:36:12 by bgonzale          #+#    #+#             */
/*   Updated: 2019/06/24 14:28:05 by bgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>

typedef struct			s_list
{
	char			*name;
	struct stat		ss;
	struct s_list	*next;
	time_t			time;
	long			ntime;
}						t_list;

int		ft_strchr(const char *s, char ch)
{
	while (*s != ch && *s != '\0')
		s++;
	if (*s == ch)
		return (1);
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

t_list	*ft_create_elem(char *name, struct stat ss)
{
    t_list	*node;

    node = NULL;
    node = (t_list *)malloc(sizeof(t_list));
    if (node)
    {
		node->name = name;
		node->ss = ss;
		node->time = ss.st_mtimespec.tv_sec;
		node->ntime = ss.st_mtimespec.tv_nsec;
        node->next = NULL;
    }
    return (node);
}

void	ft_lst_psh_bck(t_list **begin_list, char *name, struct stat ss)
{
    t_list *list;

    list = *begin_list;
    if (list)
    {
        while (list->next)
            list = list->next;
        list->next = ft_create_elem(name, ss);
    }
    else
        *begin_list = ft_create_elem(name, ss);
}

t_list	*ft_create(char *path, t_list *lst, int a_f)
{
	DIR				*dir;
	struct dirent	*sd;
	struct stat		ss;
	struct stat		isdir;
	char			*route;

	lstat(path, &isdir);
	if (S_ISDIR(isdir.st_mode))
	{
		dir = opendir(path);
		while ((sd = readdir(dir)) != NULL)
		{
			route = ft_routecat(path, sd->d_name, route);
			lstat(route, &ss); // Get File Data From File Name.
			if (a_f == 1)
			{
				ft_lst_psh_bck(&lst, route, ss); // Create Nodes.
			}
			else if (a_f == 0)
			{
				if (sd->d_name[0] != '.')
				{
					ft_lst_psh_bck(&lst, route, ss);
				}
			}
		}
		closedir(dir);
	}
	else
	{
		lstat(path, &ss);
		ft_lst_psh_bck(&lst, path, ss);
	}
	return (lst);
}

t_list	*ft_lst_swap(t_list *p1, t_list *p2)
{
	p1->next = p2->next;
	p2->next = p1;
	return (p2);
}

void	ft_print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s\n", lst->name);
        lst = lst->next;
    }
}

t_list	*ft_bsort(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
		lst = ft_lst_swap(lst, lst->next);
	lst->next = ft_bsort(lst->next);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
	{
		lst = ft_lst_swap(lst, lst->next);
		lst->next = ft_bsort(lst->next);
	}
	return (lst);
}

t_list	*ft_rsort(t_list *lst)
{
	t_list *a;
	t_list *b;
	t_list *c;

	a = NULL;
	b = lst;
	c = lst->next;
	while (b)
	{
		c = b->next;
		b->next = a;
		a = b;
		b = c;
	}
	return (a);
}

t_list	*ft_tsort(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && (lst->time < lst->next->time))
		lst = ft_lst_swap(lst, lst->next);
	else if (lst->next && lst->time == lst->next->time)
		if (lst->next && (lst->ntime < lst->next->ntime))
			lst = ft_lst_swap(lst, lst->next);
	lst->next = ft_tsort(lst->next);
	if (lst->next && (lst->time < lst->next->time))
	{
		lst = ft_lst_swap(lst, lst->next);
		lst->next = ft_tsort(lst->next);
	}
	else if (lst->next && lst->time == lst->next->time)
	{
		if (lst->next && (lst->ntime < lst->next->ntime))
		{
			lst = ft_lst_swap(lst, lst->next);
			lst->next = ft_tsort(lst->next);
		}
	}
	return (lst);
}

void	ft_gettime(t_list *lst)
{
	char	*date_time;

	date_time = ctime(&(lst->time));
	printf("%.6s %.5s ", (date_time + 4), (date_time + 11));
}

void	ft_l_flag(char *path, t_list *lst)
{
	struct stat		isdir;
	struct passwd	*pwd;
	struct group	*grp;
	long			block_size;
	t_list			*ptr;

	lstat(path, &isdir);
	block_size = 0;
	ptr = lst;
	while (ptr) // Get Block Size
	{
		block_size += ptr->ss.st_blocks;
		ptr = ptr->next;
	}
	if (S_ISDIR(isdir.st_mode))
		printf("total %ld\n", block_size);
	while (lst)
	{
		printf((S_ISDIR(lst->ss.st_mode)) ? "d" : "-"); // Permisions.
		printf((lst->ss.st_mode & S_IRUSR) ? "r" : "-");
		printf((lst->ss.st_mode & S_IWUSR) ? "w" : "-");
		printf((lst->ss.st_mode & S_IXUSR) ? "x" : "-");
		printf((lst->ss.st_mode & S_IRGRP) ? "r" : "-");
		printf((lst->ss.st_mode & S_IWGRP) ? "w" : "-");
		printf((lst->ss.st_mode & S_IXGRP) ? "x" : "-");
		printf((lst->ss.st_mode & S_IROTH) ? "r" : "-");
		printf((lst->ss.st_mode & S_IWOTH) ? "w" : "-");
		printf((lst->ss.st_mode & S_IXOTH) ? "x" : "-"); // End.
		printf(" %2u ", lst->ss.st_nlink); // Number of hard links to the file.
		pwd = getpwuid(lst->ss.st_uid); // Get User ID.
		grp = getgrgid(lst->ss.st_gid); // Get Group ID Of File.
		printf("%s  %s", pwd->pw_name, grp->gr_name); // Print Group ID.
		printf("%6lld ", lst->ss.st_size); // File Size.
		ft_gettime(lst); // Get Time & Print.
		printf("%s\n", lst->name); // Print File Name
		lst = lst->next; // Moves From First Node - Last And Sets Last Node Head To NULL.
	}
}

void	ft_exe_flags(char *path, t_list *lst, int t_f, int r_f, int l_f, int a_f, int no_f)
{
	int print_exe = t_f + r_f + l_f + a_f;
	printf("print_exe = [%d]\n", print_exe);
	lst = ft_create(path, lst, a_f); // Create list & Gather Data.
	lst = ft_bsort(lst); // Sort by a-z.
	if (t_f == 1)
	{
		lst = ft_tsort(lst);
		if (print_exe == 1)
			ft_print_list(lst);
	}
	if (r_f == 1)
	{
		lst = ft_rsort(lst);
		if (print_exe == 1)
			ft_print_list(lst);
	}
	if (l_f == 1)
		ft_l_flag(path, lst);
	if (a_f == 1)
		if (print_exe == 1)
			ft_print_list(lst);
	if (no_f == 1 || (print_exe == 2 && l_f == 0) || (print_exe == 3 && l_f == 0))
		ft_print_list(lst);
	free(lst);
}

void	ft_find_flags(char *path, t_list *lst, char *argv)
{
	int		t_flag = 0;
	int		r_flag = 0;
	int		l_flag = 0;
	int		a_flag = 0;
	int		no_flag = 0;

	if (ft_strchr(argv, 't') == 1)
		t_flag = 1;
	if (ft_strchr(argv, 'r') == 1)
		r_flag = 1;
	if (ft_strchr(argv, 'l') == 1)
		l_flag = 1;
	if (ft_strchr(argv, 'a') == 1)
		a_flag = 1;
	if (t_flag == 0 && r_flag == 0 && l_flag == 0 && a_flag == 0)
		no_flag = 1;
	printf("t = [%d] r = [%d] l = [%d] a = [%d] no_flag = [%d]\n", t_flag, r_flag, l_flag, a_flag, no_flag);
	ft_exe_flags(path, lst, t_flag, r_flag, l_flag, a_flag, no_flag);
}

int		main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*sd;
	char			*path;
	t_list			*lst;

	path = argv[2];
	printf("Path = [%s]\n", path);
	lst = NULL;
	if (argc == 1)
		ft_find_flags(path, lst, "");
	else
		ft_find_flags(path, lst, argv[1]);
	return (0);
}
