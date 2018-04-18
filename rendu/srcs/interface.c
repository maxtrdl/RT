/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:42:48 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 19:41:59 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		free_string_put(t_env *e, int x, int y, char *str)
{
	mlx_string_put(e->mlx, e->win, x, y, 0x00FFFFFF, str);
	free(str);
}

void		selected_form(t_env *e)
{
	if (e->s->forms[e->choice]->form_id == 0)
		mlx_string_put(e->mlx, e->win, 1195, 10, 0x00FFFFFF, "Light");
	else if (e->s->forms[e->choice]->form_id == 2)
		mlx_string_put(e->mlx, e->win, 1195, 10, 0x00FFFFFF, "Sphere");
	else if (e->s->forms[e->choice]->form_id == 1)
		mlx_string_put(e->mlx, e->win, 1195, 10, 0x00FFFFFF, "Plane");
	else if (e->s->forms[e->choice]->form_id == 3)
		mlx_string_put(e->mlx, e->win, 1195, 10, 0x00FFFFFF, "Cylinder");
	else if (e->s->forms[e->choice]->form_id == 4)
		mlx_string_put(e->mlx, e->win, 1195, 10, 0x00FFFFFF, "Cone");
	else if (e->s->forms[e->choice]->form_id == 7)
		mlx_string_put(e->mlx, e->win, 1190, 10, 0x00FFFFFF, "Hyperboloid");
}

void		no_form_selected(t_env *e)
{
	if (e->choice == -1 && e->lev > -1)
	{
		mlx_string_put(e->mlx, e->win, 1195, 10, 0x00FFFFFF, "Camera");
		free_string_put(e, 1195, 65, ft_ftoa(e->factx));
		free_string_put(e, 1195, 95, ft_ftoa(e->facty));
		free_string_put(e, 1195, 125, ft_ftoa(e->factz));
		free_string_put(e, 1195, 185, ft_ftoa(e->s->camx));
		free_string_put(e, 1195, 215, ft_ftoa(e->s->camy));
		free_string_put(e, 1195, 245, ft_ftoa(e->s->camz));
		mlx_string_put(e->mlx, e->win, 1195, 305, 0x00ffffff, "N/A");
		mlx_string_put(e->mlx, e->win, 1195, 335, 0x00ffffff, "N/A");
		mlx_string_put(e->mlx, e->win, 1195, 365, 0x00ffffff, "N/A");
	}
	if (e->choice != -1 && e->s->forms[e->choice]->form_id == 2)
	{
		mlx_string_put(e->mlx, e->win, 1195, 65, 0x00ffffff, "N/A");
		mlx_string_put(e->mlx, e->win, 1195, 95, 0x00ffffff, "N/A");
		mlx_string_put(e->mlx, e->win, 1195, 125, 0x00ffffff, "N/A");
	}
}

void		aff_dash_infos(t_env *e)
{
	if (e->choice != -1)
	{
		selected_form(e);
		if (e->s->forms[e->choice]->form_id != 2)
		{
			free_string_put(e, 1195, 65,
					ft_ftoa(e->s->forms[e->choice]->norm.x));
			free_string_put(e, 1195, 95,
					ft_ftoa(e->s->forms[e->choice]->norm.y));
			free_string_put(e, 1195, 125,
					ft_ftoa(e->s->forms[e->choice]->norm.z));
		}
		free_string_put(e, 1195, 185, ft_ftoa(e->s->forms[e->choice]->pos.x));
		free_string_put(e, 1195, 215, ft_ftoa(e->s->forms[e->choice]->pos.y));
		free_string_put(e, 1195, 245, ft_ftoa(e->s->forms[e->choice]->pos.z));
		free_string_put(e, 1195, 305, ft_ftoa(e->s->forms[e->choice]->col.r));
		free_string_put(e, 1195, 335, ft_ftoa(e->s->forms[e->choice]->col.g));
		free_string_put(e, 1195, 365, ft_ftoa(e->s->forms[e->choice]->col.b));
	}
	if (e->choice == -1 || e->s->forms[e->choice]->form_id == 2)
		no_form_selected(e);
}

void		colors_gradient(t_env *e, float v, double dv)
{
	dv = 1 - 0;
	if (v < (0 + 0.25 * dv))
	{
		e->s->forms[e->choice]->col.r = 0;
		e->s->forms[e->choice]->col.g = 4 * (v - 0) / dv;
	}
	else if (v < (0 + 0.5 * dv))
	{
		e->s->forms[e->choice]->col.r = 0;
		e->s->forms[e->choice]->col.b = 1 + 4 * (0 + 0.25 * dv - v) / dv;
	}
	else if (v < (0 + 0.75 * dv))
	{
		e->s->forms[e->choice]->col.r = 4 * (v - 0 - 0.5 * dv) / dv;
		e->s->forms[e->choice]->col.b = 0;
	}
	else
	{
		e->s->forms[e->choice]->col.g = 1 + 4 * (0 + 0.75 * dv - v) / dv;
		e->s->forms[e->choice]->col.b = 0;
	}
}
