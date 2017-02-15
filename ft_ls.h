/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzheng <dzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 18:05:59 by dzheng            #+#    #+#             */
/*   Updated: 2017/02/15 18:21:32 by dzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <time.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <dirent.h>
# include <string.h>

# define LS_FLAGS "GRaflrt1"

/*
** Colors
*/

# define NORMAL "\e[0m"
# define BOLD "\e[1m"
# define UNDERLINED "\e[4m"
# define BLINK "\e[5m"
# define BLACK "\e[30m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define LIGHT_GRAY "\e[37m"
# define DARK_GRAY "\e[90m"
# define LIGHT_RED "\e[91m"
# define LIGHT_GREEN "\e[92m"
# define LIGHT_YELLOW "\e[93m"
# define LIGHT_BLUE "\e[94m"
# define LIGHT_MAGENTA "\e[95m"
# define LIGHT_CYAN "\e[96m"
# define WHITE "\e[97m"
# define MATRIX "\e[5;32m"

typedef struct		s_pls
{
	char			mode[15];
	int				links;
	char			*own;
	char			*group;
	int				major;
	long long		size;
	long long		blocks;
	long			date;
	char			*name;
	char			*linkpath;
	int				not_a_dir;
}					t_pls;

void				ft_fix(const t_pls *info, const uint *padd, char **color, \
					char *date);

void				ft_ls(const char *path, const char *flags, int args);
t_list				*ft_ls_back(const char *path, const char *flags);
void				ft_ls_front(const t_list *lst, const char *flags, \
					const char *path, int args);
void				ft_ls_rec(const t_list *lst, const char *path, \
					const char *flags);
t_list				*ft_ls_sort(t_list *lst, const char *flags);
void				ft_ls_args(int ac, char **av, int first, const char *flags);
int					ft_ls_error_file_dir(const char *path);
t_list				*ft_ls_listsort(t_list *lst, int (*cmp)(void*, void*));
long				errors(const int error, const char *letter);
int					ft_ls_colors(const t_pls *info, const char *flags);

# define MODE 0
# define LNKS 1
# define OWN 2
# define GROUP 3
# define MAJ 4
# define SIZE 5
# define DATE 6
# define ARGS 9
# define FILENAMEMAXLEN 255
# define COLORS 10

#endif
