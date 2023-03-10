/*There are no mistakes, just happy accidents... And segfaults.*/

#include "../include/cub3d.h"

/*	while i don't hit anything, i keep walking around the grid
	adding the distance for later reference
	rc->side:  this will later indicate which texture to be used 
	Ex.: (Side 1 = NO, Side 2 = SO,  Side 3 = EA, Side 4 = WE)	*/
void	dda_time(t_ray *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dis_x < rc->side_dis_y)
		{
			rc->side_dis_x += rc->delta_dis_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dis_y += rc->delta_dis_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (rc->map[rc->map_y][rc->map_x] == '1')
			rc->hit = 1;
	}
}

//This function starts by projecting ceiling and floor all over
// Then, while loop goes thrugh every 'i' is a slice in the screen
// We calculateray position and direction and determines which
//axis is first hit and we calculate the distance to a wall (collision)
// We calculate size of line to be drawn and draw it on scree.
void	raycaster(t_game *g)
{
	int	i;

	i = -1;
	floor_n_ceiling(g);
	while (++i < WIDTH)
	{
		g->rc->hit = 0;
		set_ray_posdir(g, i);
		set_step(g->rc);
		dda_time(g->rc);
		set_line_len(g);
		texture_calculation(g);
		draw_texture_line(g, g->tex->no, g->tex->n, i);
	}
}

//DEBUG PRINT
		/* if ((int)i % 320 == 0 || i ==480 || i == 959)
			printf("\t[%d]\tcameraX = %f / raydirX = %f / raydirY = %f / deltadistX = %f / deltadisY = %f / sidedisX = %f / sidedisY = %f\n", (int)i, g->rc->camera_x, g->rc->ray_dir_x, g->rc->ray_dir_y, g->rc->delta_dis_x, g->rc->delta_dis_y, g->rc->side_dis_x, g->rc->side_dis_y);*/
