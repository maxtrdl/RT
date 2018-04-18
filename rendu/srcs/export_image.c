/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrudel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:51:59 by mtrudel           #+#    #+#             */
/*   Updated: 2018/03/06 13:16:40 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

static void			file_header(t_env *e, int fd)
{
	int				data[3];

	write(fd, "BM", 2);
	data[0] = (unsigned int)(e->width * e->height) + 54;
	data[1] = 0;
	data[2] = 54;
	write(fd, (char*)data, 12);
}

static void			image_header(t_env *e, int fd)
{
	int				data[10];

	data[0] = 40;
	data[1] = (int)e->width;
	data[2] = (int)e->height;
	data[3] = 1 + 24 * 256 * 256;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;
	data[8] = 0;
	data[9] = 0;
	write(fd, (char*)data, 40);
}

static void			bgr_image(t_env *e, int fd)
{
	char	*buf;
	int		x;
	int		y;
	int		i;

	y = e->height;
	i = 0;
	buf = (char *)malloc(sizeof(char) * ((int)(e->width * e->height * 3)));
	while (--y >= 0)
	{
		x = 0;
		while (x < e->width)
		{
			buf[i] = e->image[x][y].b * 255 > 255 ? (char)255 : (char)\
			((int)(e->image[x][y].b * 255));
			buf[i + 1] = e->image[x][y].g * 255 > 255 ? (char)255 : \
			(char)((int)(e->image[x][y].g * 255));
			buf[i + 2] = e->image[x][y].r * 255 > 255 ? (char)255 : \
			(char)((int)(e->image[x][y].r * 255));
			i += 3;
			x++;
		}
	}
	write(fd, buf, i);
	free(buf);
}

static void			export_image_2(t_env *e, int fd)
{
	e->export_count++;
	file_header(e, fd);
	image_header(e, fd);
	bgr_image(e, fd);
	close(fd);
}

void				export_image(t_env *e)
{
	int		fd;
	char	*tmp;
	char	*filename;
	char	*num;
	mode_t	mode;

	fd = 0;
	num = ft_itoa(e->export_count);
	tmp = (ft_strjoin("image", num));
	filename = ft_strjoin(tmp, ".bmp");
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (e->export_count <= 20)
	{
		if ((fd = creat(filename, mode)) == -1)
			ft_exit("export failed");
		ft_putstr("export image -------------------> ");
		ft_putendl(filename);
		export_image_2(e, fd);
	}
	free(filename);
	free(tmp);
	free(num);
}
