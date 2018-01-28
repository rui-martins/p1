/*
 * This file is part of "2º Projeto de Introdução à Computação 2017/2018"
 * (2oPIC1718).
 *
 * 2oPIC1718 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 2oPIC1718 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 2oPIC1718. If not, see <http://www.gnu.org/licenses/>.
 * */

/**
 * @file
 * Implementation of the interface defined in showworld.h which displays an
 * ASCII-based visualization of the current state of the simulation world.
 *
 * @note Students should change or replace this file with a new implementation
 * making use of graphical or game library.
 *
 * @author Nuno Fachada
 * @date 2018
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 * */

#include "showworld.h"
#include <stdio.h>
#include <stdlib.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"

/* The implementation of `SHOWWORLD` type used in this simple text-based world
 * visualization code. In this simple case, we only need to keep track of the
 * world dimensions and of the function pointer which knows how to read an
 * agent from the world data structure.
 * */
struct showworld {
    unsigned int xdim;
    unsigned int ydim;
    get_agent_info_at aginfo_func;
};

/** Variable for the canvas **/
ALLEGRO_DISPLAY *display = NULL;
/** Variable for the font **/
ALLEGRO_FONT *font1 = NULL;

/** Variables of the drawings of the agents on the canvas **/
ALLEGRO_BITMAP *h_playable = NULL;
ALLEGRO_BITMAP *h_ai = NULL;
ALLEGRO_BITMAP *z_playable = NULL;
ALLEGRO_BITMAP *z_ai = NULL;
ALLEGRO_BITMAP *none = NULL;
/** Variables for the width and height of the agents **/
int agent_width = 0, agent_height = 0;
/* Create a new display/visualization object for the simulation world.
 *
 * This function obeys the `showworld_new()` prototype defined in
 * `showworld.h`. */
SHOWWORLD *showworld_new(
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at aginfo_func) {

    /** Initialize allegro's functions and addons **/
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    SHOWWORLD *sw = NULL;
    sw = malloc(sizeof(SHOWWORLD));
    sw->xdim = xdim;
    sw->ydim = ydim;
    sw->aginfo_func = aginfo_func;

    /** Define agent width and height with the proportions to fit on
    a 600 by 600 display **/
    agent_width = 600/(sw->xdim);
    agent_height = 600/(sw->ydim);

    /** Initialize the window display with a fixed size of 600 by 600 **/
    if((sw->xdim) == (sw->ydim)) {
      display = al_create_display(600,600);
    }
    /** Initialize the window display with a width of 600 and
    a height that maintains the proportions of the objects that'll be drew **/
    if((sw->xdim) > (sw->ydim)) {
      display = al_create_display((sw->xdim)*agent_width,
                                  (sw->ydim)*agent_width);
    }
    /** Initialize the window display with a height of 600 and
    a width that maintains the proportions of the objects that'll be drew **/
    if((sw->xdim) < (sw->ydim)) {
      display = al_create_display((sw->xdim)*agent_height,
                                  (sw->ydim)*agent_height);
    }

    /** We do this so that the display draws all of the agents as squares **/
    if((sw->xdim) > (sw->ydim)) {
      agent_height = 600/(sw->xdim);
    } else {
      agent_width = 600/(sw->ydim);
    }

    /** Load the respective images of each agent **/
    h_playable = al_load_bitmap("Human1.png");
    h_ai = al_load_bitmap("Human2.png");
    z_playable = al_load_bitmap("Zombie1.png");
    z_ai = al_load_bitmap("Zombie2.png");
    none = al_load_bitmap("Bg.png");

    /** Load the fonts that are going to be used and their respective size **/
    if((sw->xdim) >= (sw->ydim)) {
      font1 = al_load_font("uni0553.ttf",600/((sw->xdim)*3),0);
    } else {
      font1 = al_load_font("uni0553.ttf",600/((sw->ydim)*3),0);
    }

    /** Clear the background's color (just a precaution) **/
    al_clear_to_color(al_map_rgb(0,0,0));

    return sw;

}

/* Destroy a display/visualization object for the simulation world.
 *
 * This function obeys the `showworld_destroy()` prototype defined in
 * `showworld.h`. */
void showworld_destroy(SHOWWORLD *sw) {

    /** Clear the memory **/
    al_destroy_bitmap(h_playable);
    al_destroy_bitmap(h_ai);
    al_destroy_bitmap(z_playable);
    al_destroy_bitmap(z_ai);
    al_destroy_display(display);
    free(sw);
}

/* Update the simulation world display/visualization.
 *
 * This function obeys the `showworld_update()` prototype defined in
 * `showworld.h`. */
void showworld_update(SHOWWORLD *sw, void *w) {

    /** Cycle through all the rows **/
    for (unsigned int y = 0; y < sw->ydim; ++y) {

        /** Cycle through all the columns for the current row **/
        for (unsigned int x = 0; x < sw->xdim; ++x) {

            /** Get state of the world (in bit packed fashion) using the user
               supplied function. **/
            unsigned int item = sw->aginfo_func(w, x, y);

            /** Extract the agent type (2 bits). **/
            AGENT_TYPE ag_type = item & 0x3;
            /** Extract whether the agent is playable (1 bit). **/
            unsigned char playable = (item >> 2) & 0x1;
            /** Extract the agent ID (16 bits). **/
            unsigned short ag_id = (item >> 3) & 0xFFFF;

            /** Determine the agent type. **/
            switch (ag_type) {

                /** If no agent is present at (x,y), draw Bg. **/
                case None:
                    al_draw_scaled_bitmap(none, 0, 0, 32, 32,
                                          x*agent_width, y*agent_height,
                                          agent_width, agent_height, 0);
                    break;

                /** If human agent present at (x,y) draw Human1 or Human2. **/
                case Human:
                    if (playable) {
                        /** Human1 for player-controlled human agent. **/
                        al_draw_scaled_bitmap(h_playable, 0, 0, 32, 32,
                                              x*agent_width, y*agent_height,
                                              agent_width, agent_height, 0);
                    } else {
                        /** Human2 for AI-controlled human agent. **/
                        al_draw_scaled_bitmap(h_ai,  0, 0, 32, 32,
                                              x*agent_width, y*agent_height,
                                              agent_width, agent_height, 0);
                    }
                    /** Print the agent ID in front of it's image. **/
                    al_draw_textf(font1, al_map_rgb(255,255,255),
                                  x*agent_width, y*agent_height,
                                  0, "%i", ag_id);
                    break;

                /** If zombie agent present at (x,y) draw Zombie1 or Zombie2. **/
                case Zombie:
                    if (playable) {
                        /** Zombie1 for player-controlled zombie agent. **/
                        al_draw_scaled_bitmap(z_playable, 0, 0, 32, 32,
                                              x*agent_width, y*agent_height,
                                              agent_width, agent_height, 0);
                    } else {
                        /** Zombie2 for AI-controlled zombie agent. **/
                        al_draw_scaled_bitmap(z_ai, 0, 0, 32, 32,
                                              x*agent_width, y*agent_height,
                                              agent_width, agent_height, 0);
                    }
                    /** Print the agent ID in front of the image. **/
                    al_draw_textf(font1, al_map_rgb(200,0,0),
                                  x*agent_width, y*agent_height,
                                  0, "%i", ag_id);
                    break;

                /** Print '?' if unknown type detected. This should *never*
                   happen. **/
                default:
                    al_draw_text(font1, al_map_rgb(255,255,255),
                                 x*agent_width, y*agent_height,
                                 0, "?");

            }
        }
    }
    /** We call this function so that the objects can be seen on the
    display, without it the display would be black**/
    al_flip_display();
}
