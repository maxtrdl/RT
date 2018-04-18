/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlajovec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 23:38:54 by jlajovec          #+#    #+#             */
/*   Updated: 2018/03/06 18:52:16 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <pthread.h>
# include "./define.h"

typedef struct		s_col
{
	float			r;
	float			g;
	float			b;
}					t_col;

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_form
{
	int				form_id;

	t_vec			pos;
	t_vec			norm;
	t_col			col;

	float			rad;
	float			high;
	float			cos;
	float			sin;
}					t_form;

typedef struct		s_sce
{
	char			*name;
	char			*tmp;

	int				shadow;
	int				shine;
	int				light;
	int				coor;
	int				nb_lights;
	int				anti;
	int				blur;

	float			camx;
	float			camy;
	float			camz;
	float			cam_normx;
	float			cam_normy;
	float			cam_normz;

	t_form			**forms;
}					t_sce;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*limg;
	void			*dimg;

	char			*data;
	char			imagr;
	char			imagb;
	char			imagg;
	char			**map;

	int				choice;
	int				bpp;
	int				sl;
	int				endn;
	int				fd;
	int				param;
	int				inits;
	int				t;
	int				i;
	int				j;
	int				form_hit;
	int				form_light_hit;
	int				light_hit;
	int				nb_plane;
	int				avoid;
	int				lev;
	int				lev_tmp;
	int				mouse;
	int				nb_refrac;
	int				nb_forms;
	int				flagangle;
	int				color_move;
	int				export_count;
	int				rt_activate;
	int				sepia;
	int				bnw;
	int				reflexion;
	int				bdperlin;

	float			width;
	float			height;
	float			more;
	float			shininess;
	float			pixnormx;
	float			pixnormy;
	float			pixremapx;
	float			pixremapy;
	float			pixcamx;
	float			pixcamy;
	float			imgratio;
	float			lenvec;
	float			t0;
	float			mint;
	float			t0p;
	float			thc;
	float			red;
	float			green;
	float			blue;
	float			movex;
	float			movey;
	float			movez;
	float			factx;
	float			facty;
	float			factz;
	float			angle;
	float			t1;
	float			t2;
	float			tca;
	float			intensity;
	float			rad_form;
	float			coef;
	float			coef_ref;
	float			reflet;

	t_col			diffusecol;
	t_col			speculcol;
	t_col			lightint;
	t_col			**image;
	t_col			color_ref;

	t_vec			ambient;
	t_vec			diffuse;
	t_vec			p0;
	t_vec			reflection;
	t_vec			specular;
	t_vec			pcamspace;
	t_vec			raydir;
	t_vec			normal;
	t_vec			lightpos;
	t_vec			rayo;
	t_vec			lightray;
	t_vec			angle_cam;
	t_vec			n_ref;

	pthread_t		thread[NBTHREAD];

	struct s_env	*r[NBTHREAD];

	t_sce			*s;

}					t_env;

/*
**	main.c
*/
void				ft_exit(char *s);
void				closing(t_env *e);
void				rt(t_env *e);
int					main(int ac, char **av);

/*
**	build_map.c
*/
void				parser(t_env *e, int fd);
void				stock_params(t_env *e, char *line, int line_nb);

/*
**	check_params.c
*/
void				check_params(t_env *e, t_sce *s, int line_nb);
void				params_send(t_env *e, t_sce *s, int i);
int					check_form(t_env *e, t_sce *s, int i);
void				set_form(t_sce *s, int i, int form_id);

/*
**	parse_plane.c
*/
int					check_plane(t_env *e, t_sce *s, int p, int x);
int					stock_plane(t_sce *s, int coor_num, int j, int p);
void				stock_plane2(t_sce *s, int coor_num, int p);
int					stock_plane_colors(t_sce *s, int coor_num, int p);

/*
**	parse_sphere.c
*/
int					stock_sphere_colors(t_sce *s, int coor_num, int p);
int					stock_sphere(t_sce *s, int coor_num, int j, int p);
void				stock_sphere2(t_sce *s, int coor_num, int p);
int					check_sphere(t_env *e, t_sce *s, int p, int x);

/*
**	check_config_1.c
*/
int					check_intensity(t_env *e, t_sce *s, int p, int x);
int					stock_camera(t_sce *s, int coor_num, int j);
void				stock_camera2(t_sce *s, int coor_num);
int					check_camera(t_env *e, t_sce *s, int param_nb, int x);

/*
**	check_config_2.c
*/
int					check_shine(t_env *e, t_sce *s, int p);
int					check_shadow(t_env *e, t_sce *s, int p, int x);

/*
**	check_config_3.c
*/
int					final_check_forms(t_env *e, t_sce *s, int p, int f_id);
int					count_result(int count, int f_id);
int					check_name(t_env *e, t_sce *s, int param_nb);
int					check_form3(t_env *e, t_sce *s, int i);
int					check_form2(t_env *e, t_sce *s, int i);

/*
**	levels.c
*/
void				levdiffuse(t_env *e, int i, t_vec tmp);
void				levspecular(t_env *e);
void				levels(t_env *e);

/*
**	parse_light.c
*/
int					stock_light_colors(t_sce *s, int coor_num, int p);
void				stock_light2(t_sce *s, int coor_num, int p);
int					stock_light(t_sce *s, int coor_num, int j, int p);
int					check_light(t_env *e, t_sce *s, int p, int x);

/*
**	parse_cylinder.c
*/
int					stock_cylinder_colors(t_sce *s, int coor_num, int p);
void				stock_cylinder2(t_sce *s, int coor_num, int p);
int					stock_cylinder(t_sce *s, int coor_num, int j, int p);
int					check_cylinder(t_env *e, t_sce *s, int p, int x);

/*
**	parse_cone.c
*/
int					stock_cone_colors(t_sce *s, int coor_num, int p);
void				stock_cone2(t_sce *s, int coor_num, int p);
int					stock_cone(t_sce *s, int coor_num, int j, int p);
int					check_cone(t_env *e, t_sce *s, int p, int x);

/*
**	parse_hyperbol.c
*/
int					stock_hyperbol_colors(t_sce *s, int coor_num, int p);
void				stock_hyperbol2(t_sce *s, int coor_num, int p);
int					stock_hyperbol(t_sce *s, int coor_num, int j, int p);
int					check_hyperbol(t_env *e, t_sce *s, int p, int x);

/*
**	display_op.c
*/
void				aff_img(t_env *e);
void				put_pixel(t_env *e, int x, int xmax);
void				init_image(t_env *e);
void				import_ressources(t_env *e);

/*
**	init_vec.c
*/
t_col				col(void);
t_vec				vec(void);
void				init_main(t_env *e);

/*
**	threads_op.c
*/
t_env				*init_struct(t_env *e);
void				threads_launch(t_env *e);

/*
**	key.c
*/
int					keyhook(int k, t_env *e);
int					keyhook2(int k, int re, t_env *e);
int					keyhook3(int k, int re, t_env *e);
int					keyhook4(int k, int re, t_env *e);
int					keyhook5(int k, int re, t_env *e);

/*
**	mouse.c
*/
int					mouse_key(int button, int x, int y, t_env *e);
int					obj_select(t_env *e, int x, int y);

/*
**	interface2.c
*/
int					mouse_hoover(int x, int y, void *param);
int					pos_to_percent(t_env *e, int x, int y, int re);
void				effects_stats(t_env *e, int x, int y);
void				dash_arrows(int x, int y, t_env *e);
int					mouse_key_dash(int button, int x, int y, t_env *e);

/*
**	interface.c
*/
void				free_string_put(t_env *e, int x, int y, char *str);
void				selected_form(t_env *e);
void				no_form_selected(t_env *e);
void				aff_dash_infos(t_env *e);
void				colors_gradient(t_env *e, float v, double dv);

/*
**	raytracer.c
*/
void				do_hit(t_env *e, int k, int hit);
void				*raytracer(void *e);
void				raytracer_routine(t_env *e);
int					intersect(t_env *e, t_vec *rayo, t_vec *raydir, t_form *f);

/*
**	init_raytracer.c
*/
void				init_raytracer(t_env *e);
void				raytracer_loop(t_env *e, int i, int j);

/*
**	calcs.c
*/
float				dot(t_vec a, t_vec b);
t_vec				vec_sub(t_vec *a, t_vec *b);
t_vec				vec_add(t_vec *a, t_vec *b);
t_vec				prod_matr(float r, t_vec *m);
t_vec				vec_normalize(t_vec *v);

/*
**	intersect.c
*/
int					intersect_plane(t_env *e, t_vec **rayo, \
	t_vec **raydir, t_form *f);
int					resolve_quadratic(t_env *e, float det, float a, float b);
void				ft_swap(t_env *e);

/*
**	intersect2.c
*/
int					intersect_hyperboloid(t_env *e, t_vec **rayo, \
		t_vec **raydir, t_form *f);
int					intersect_sphere(t_env *e, t_vec **rayo, \
		t_vec **raydir, t_form *f);
int					intersect_cone(t_env *e, t_vec **rayo, \
		t_vec **raydir, t_form *f);
int					intersect_cylinder(t_env *e, t_vec **rayo, \
		t_vec **raydir, t_form *f);

/*
**	light.c
*/
void				lightset(t_env *e, int i);
void				ambient_set(t_col c, t_vec ambient);
void				diffuse(t_env *e);
void				reflection(t_env *e);
void				specular(t_env *e);

/*
**	norm.c
*/
void				norm_calc_cone_cylinder(t_env *e, t_form *f, t_vec *n);
void				norm_init(t_env *e);
void				norm_caps(t_env *e, t_form *f, t_vec *n);
void				norm_calc_plane(t_env *e, t_form *f, t_vec *n);
void				norm_calc_sphere(t_env *e, t_form *f, t_vec *n);

/*
**	image.c
*/
void				fill_image(t_env *e);
void				light_hit(t_env *e, int f);
void				fill_image_light(t_env *e, int f);
void				dark_image(t_env *e);
void				save_col(t_env *e);
/*
**	calcs2.c
*/
float				maxdata(float x, float y);
void				calcangle(t_form *f);
float				dot2(t_vec a, t_vec b);
void				post_calc_aa(t_env *e, int x, int y);

/*
**	shadows.c
*/
void				shadow(t_env *e);

/*
**	rotation.c
*/
void				rot_x(t_env *e);
void				rot_y(t_env *e);
void				rot_z(t_env *e);

/*
**	rothit.c
*/
void				rothit_x(t_env *e);
void				rothit_y(t_env *e);
void				rothit_z(t_env *e);

/*
**	export_config
*/
void				write_spheres(t_env *e, int fd, int i);
void				write_win_set(t_env *e, int fd);
void				write_cam_set(t_env *e, int fd);
char				*create_file(t_env *e, int conf_nb);
void				write_in_file(t_env *e);

/*
**	export_config2
*/
void				write__normal_light(t_env *e, int fd, int i, char *tmp);
void				write_lights(t_env *e, int fd, int i);
void				write_planes(t_env *e, int fd, int i);
void				write_co_cy(t_env *e, int fd, int i);
void				free_write(float n, int fd, int type);

/*
**	export_config3
*/
void				write_hyper(t_env *e, int fd, int i);

/*
**	rotforms.c
*/
void				rotformz(t_form *f, int a);
void				rotformx(t_form *f, int a);
void				rotformy(t_form *f, int a);

/*
**	caps.c
*/
void				intersect_caps2(t_env *e, t_vec *rayo, \
		t_vec *raydir, t_form *f);
float				intersect_caps(t_env *e, t_vec *rayo, \
		t_vec *raydir, t_form *f);
float				caps2(t_env *e, t_vec *rayo, t_vec *raydir, t_form *f);
float				caps(t_env *e, t_vec *rayo, t_vec *raydir, t_form *f);

/*
**	expor_image.c
*/
void				export_image(t_env *e);

/*
**	add_objects.c
*/
void				obj_spec(t_env *e, int obj_id, int i);
void				add_object(t_env *e, int obj_id);

/*
**	filter.c
*/
void				sepia(t_env *e, int x, int y, int index);
void				no_filter(t_env *e, int x, int y, int index);
void				black_white(t_env *e, int x, int y, int index);

/*
**	key2.c
*/
int					keyhook7(int k, int re, t_env *e);
int					keyhook6(int k, int re, t_env *e);

/*
**	bdperlin.c
*/
double				perlin(double x, double y, double z);

/*
**	reflexion.c
*/
void				reflexion(t_env *e);

/*
**	reflexion2.c
*/
void				norm_caps_ref(t_env *e, t_form *f, t_vec *n);
void				norm_n(t_env *e, t_vec *n, int i);
t_vec				getnorm(t_env *e, t_vec newstart, int i, t_vec *p0);
void				round_num(t_vec *v);

#endif
