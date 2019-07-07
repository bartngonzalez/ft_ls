/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonzale <bgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:52:18 by bgonzale          #+#    #+#             */
/*   Updated: 2019/06/27 20:50:00 by bgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct s_flags
{
	int R;
	int l;
	int a;
	int r;
	int t;
} t_flags;

typedef struct s_dir
{
	struct s_dir *next;
	struct s_dir *sub_dir;
} t_dir;

typedef struct s_file
{
	struct s_file *next;
} t_file;

#endif
