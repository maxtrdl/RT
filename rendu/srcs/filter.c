/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrudel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:34:16 by mtrudel           #+#    #+#             */
/*   Updated: 2018/03/06 11:24:41 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void	black_white(t_env *e, int x, int y, int index)
{
	double	tmp;

	tmp = e->image[x][y].r;
	tmp = tmp < (e->image[x][y].g) ? (e->image[x][y].g) : tmp;
	tmp = tmp < (e->image[x][y].b) ? (e->image[x][y].b) : tmp;
	e->image[x][y].r = tmp;
	e->image[x][y].g = tmp;
	e->image[x][y].b = tmp;
	e->data[index + 2] = e->image[x][y].r > 1 ? (char)(255) : \
					(char)((e->image[x][y].r) * 255);
	e->data[index + 1] = e->image[x][y].g > 1 ? (char)(255) : \
					(char)((e->image[x][y].g) * 255);
	e->data[index] = e->image[x][y].b > 1 ? (char)(255) : \
					(char)((e->image[x][y].b) * 255);
}

void	sepia(t_env *e, int x, int y, int index)
{
	double	tmp;

	tmp = e->image[x][y].r;
	tmp = tmp < (e->image[x][y].g) ? (e->image[x][y].g) : tmp;
	tmp = tmp < (e->image[x][y].b) ? (e->image[x][y].b) : tmp;
	e->image[x][y].r = tmp;
	e->image[x][y].g = tmp;
	e->image[x][y].b = tmp;
	e->image[x][y].r += 66.0 / 255;
	e->image[x][y].g += 32.0 / 255;
	e->image[x][y].b += 0.0 / 255;
	e->data[index + 2] = e->image[x][y].r > 1 ? (char)(255) : \
						(char)((e->image[x][y].r) * 255);
	e->data[index + 1] = e->image[x][y].g > 1 ? (char)(255) : \
						(char)((e->image[x][y].g) * 255);
	e->data[index] = e->image[x][y].b > 1 ? (char)(255) : \
						(char)((e->image[x][y].b) * 255);
}

void	no_filter(t_env *e, int x, int y, int index)
{
	e->data[index + 2] = e->image[x][y].r > 1 ? (char)(255) : \
						(char)((e->image[x][y].r) * 255);
	e->data[index + 1] = e->image[x][y].g > 1 ? (char)(255) : \
						(char)((e->image[x][y].g) * 255);
	e->data[index] = e->image[x][y].b > 1 ? (char)(255) : \
						(char)((e->image[x][y].b) * 255);
}
