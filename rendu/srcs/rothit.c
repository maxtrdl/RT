/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaspard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 10:25:36 by agaspard          #+#    #+#             */
/*   Updated: 2018/03/02 15:17:51 by ggaudin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		rothit_x(t_env *e)
{
	t_vec	tmp;

	e->angle = e->factx * (M_PI / 180);
	tmp.y = e->pcamspace.y;
	tmp.z = e->pcamspace.z;
	e->pcamspace.y = tmp.y * cos(e->angle) - tmp.z * sin(e->angle);
	e->pcamspace.z = tmp.y * sin(e->angle) + tmp.z * cos(e->angle);
}

void		rothit_y(t_env *e)
{
	t_vec	tmp;

	e->angle = e->facty * (M_PI / 180);
	tmp.x = e->pcamspace.x;
	tmp.z = e->pcamspace.z;
	e->pcamspace.x = tmp.x * cos(e->angle) + tmp.z * sin(e->angle);
	e->pcamspace.z = ((tmp.x * sin(e->angle)) * -1) + tmp.z * cos(e->angle);
}

void		rothit_z(t_env *e)
{
	t_vec	tmp;

	e->angle = e->factz * (M_PI / 180);
	tmp.x = e->pcamspace.x;
	tmp.y = e->pcamspace.y;
	e->pcamspace.x = tmp.x * cos(e->angle) - tmp.y * sin(e->angle);
	e->pcamspace.y = tmp.x * sin(e->angle) + tmp.y * cos(e->angle);
}
