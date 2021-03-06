/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Champi <Champi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 18:04:32 by dzheng            #+#    #+#             */
/*   Updated: 2017/02/16 01:13:50 by Champi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		modeguy(struct stat stats, char *mode)
{
	if (S_ISCHR(stats.st_mode))
		*mode++ = 'c';
	else if (S_ISFIFO(stats.st_mode))
		*mode++ = 'p';
	else if (S_ISDIR(stats.st_mode))
		*mode++ = 'd';
	else if (S_ISLNK(stats.st_mode))
		*mode++ = 'l';
	else if (S_ISBLK(stats.st_mode))
		*mode++ = 'b';
	else if (S_ISSOCK(stats.st_mode))
		*mode++ = 's';
	else if (S_ISREG(stats.st_mode))
		*mode++ = '-';
	*mode++ = (stats.st_mode & S_IRUSR ? 'r' : '-');
	*mode++ = (stats.st_mode & S_IWUSR ? 'w' : '-');
	*mode++ = (stats.st_mode & S_IXUSR ? 'x' : '-');
	*mode++ = (stats.st_mode & S_IRGRP ? 'r' : '-');
	*mode++ = (stats.st_mode & S_IWGRP ? 'w' : '-');
	*mode++ = (stats.st_mode & S_IXGRP ? 'x' : '-');
	*mode++ = (stats.st_mode & S_IROTH ? 'r' : '-');
	*mode++ = (stats.st_mode & S_IWOTH ? 'w' : '-');
	*mode = (stats.st_mode & S_IXOTH ? 'x' : '-');
	if (stats.st_mode & S_ISVTX)
		*mode = 't';
}

static int		fill_assist(t_pls *info, const char *newpath)
{
	char				buf[FILENAMEMAXLEN + 1];
	ssize_t				kneth;
	int					denz;
	struct stat			sym_stat;

	kneth = 0;
	denz = 0;
	ft_bzero(&buf, FILENAMEMAXLEN + 1);
	kneth = readlink(newpath, buf, FILENAMEMAXLEN);
	info->linkpath = (kneth == -1 ? NULL : ft_strdup(buf));
	info->major = -1;
	if (info->mode[0] == 'c' || info->mode[0] == 'b')
	{
		if (stat(newpath, &sym_stat) == -1)
			return ((int)errors(0, newpath));
		denz = sym_stat.st_rdev;
		while ((denz / 256) > 0)
			denz = denz / 256;
		info->major = denz;
		info->size = sym_stat.st_rdev % 256;
	}
	ft_memdel((void**)&newpath);
	return (0);
}

static int		fill_info(t_pls *info, char *file, \
				const char *path)
{
	struct stat			stats;
	struct passwd		*pwd;
	struct group		*grp;

	info->name = file;
	if (!path)
		return ((int)errors(0, 0));
	if (lstat(path, &stats) == -1)
		return ((int)errors(0, path) + fill_assist(info, path));
	modeguy(stats, info->mode);
	info->links = stats.st_nlink;
	info->size = stats.st_size;
	info->blocks = stats.st_blocks;
	info->date = stats.st_mtime;
	if (!(pwd = getpwuid(stats.st_uid)) || \
		!(grp = getgrgid(stats.st_gid)))
		return ((int)errors(0, path) + fill_assist(info, path));
	if (!(info->own = ft_strdup(pwd->pw_name)) || \
		!(info->group = ft_strdup(grp->gr_name)))
		errors(0, 0);
	return (fill_assist(info, path));
}

static t_list	*not_a_dir(const char *name)
{
	t_list				*lst;
	t_pls				*info;
	struct stat			stats;

	lst = NULL;
	if (stat(name, &stats) != -1 && ft_ls_error_file_dir(name) != 1)
	{
		if (!(info = ft_memalloc(sizeof(t_pls))) || \
			fill_info(info, ft_strdup(name), ft_strdup(name)) || \
			!(lst = ft_lstnew(info, sizeof(t_pls))))
			errors(0, 0);
		ft_memdel((void**)&info);
		((t_pls*)(lst->content))->not_a_dir = 1;
	}
	if (!lst)
		return ((t_list*)errors(0, name));
	return (lst);
}

t_list			*ft_ls_back(const char *path, const char *flags)
{
	t_list				*lst;
	t_list				*tmp;
	t_pls				*info;
	DIR					*dirp;
	struct dirent		*file;

	lst = NULL;
	if (!(dirp = opendir(path)))
		return (not_a_dir(path));
	while ((file = readdir(dirp)))
		if ((file->d_name)[0] != '.' || ft_strchr(flags, 'a'))
		{
			if (!(info = ft_memalloc(sizeof(t_pls))) || \
				fill_info(info, ft_strdup(file->d_name), \
				ft_strnjoin(3, path, "/", file->d_name)) || \
				!(tmp = ft_lstnew(info, sizeof(t_pls))))
				errors(0, 0);
			ft_memdel((void**)&info);
			if (!lst)
				lst = tmp;
			else
				ft_lstaddend(&lst, tmp);
		}
	(void)closedir(dirp);
	return (lst);
}
