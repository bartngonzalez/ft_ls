/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonzale <bgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:52:18 by bgonzale          #+#    #+#             */
/*   Updated: 2019/06/24 15:52:12 by bgonzale         ###   ########.fr       */
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

#endif
