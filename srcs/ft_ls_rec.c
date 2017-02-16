/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_rec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Champi <Champi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 18:04:47 by dzheng            #+#    #+#             */
/*   Updated: 2017/02/16 00:43:38 by Champi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		err_patch(DIR *dirp, char *newpath)
{
	if (!dirp && errno != ENOTDIR)
	{
		ft_printf("\n%s:\n", newpath);
		errors(0, newpath);
	}
	ft_memdel((void**)&newpath);
}

static int		dotdot(char *path)
{
	size_t		len;

	len = ft_strlen(path);
	if (path[len - 1] == '.')
	{
		if (len - 1 == 0)
			return (1);
		else if (path[len - 2] == '.')
		{
			if (len - 2 == 0)
				return (1);
			else if (path[len - 3] == '/')
				return (1);
		}
		else if (path[len - 2] == '/')
			return (1);
	}
	return (0);
}

void			ft_ls_rec(const t_list *lst, const char *path, \
				const char *flags)
{
	DIR					*dirp;
	char				*newpath;
	char				*tmp;
	char				buf[1];

	buf[0] = 0;
	while (lst)
	{
		if (!(tmp = ft_strjoin("/", ((t_pls*)(lst->content))->name)) || \
			!(newpath = ft_strjoin(path, tmp)))
			errors(0, 0);
		ft_memdel((void**)&tmp);
		if ((dirp = opendir(newpath)))
		{
			if (!dotdot(((t_pls*)(lst->content))->name) \
				&& readlink(newpath, buf, 1) == -1)
			{
				ft_printf("\n%s:\n", newpath);
				ft_ls(newpath, flags, 42);
			}
			(void)closedir(dirp);
		}
		err_patch(dirp, newpath);
		lst = lst->next;
	}
}