/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_front_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzheng <dzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 18:04:47 by dzheng            #+#    #+#             */
/*   Updated: 2017/02/15 18:08:38 by dzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_fix(const t_pls *info, const uint *padd, char **color, \
				char *date)
{
	ft_printf(" %-*s %s%s"NORMAL"%.*s%.*s\n", padd[DATE], date, \
	color[ft_ls_colors(info, "G")], info->name, \
	(info->linkpath ? -1 : 0), " -> ", (info->linkpath ? -1 : 0), \
	info->linkpath);
}

int				ft_ls_colors(const t_pls *info, const char *flags)
{
	if (!ft_strchr(flags, 'G') || info->mode[0] == '-')
		return (0);
	if (info->mode[0] == 'd')
		return (4);
	if (info->mode[0] == 'l')
		return (3);
	if (info->mode[0] == 'b')
		return (5);
	if (info->mode[0] == 'c')
		return (2);
	if (info->major >= 0)
		return (6);
	if (info->mode[3] == 'x')
		return (1);
	if (info->mode[1] == '-')
		return (7);
	return (0);
}
