//
// Created by koco on 25/04/2023.
//

#include "area.h"
#include <stdlib.h>
#include <stdio.h>
#include "shape.h"
#include "pixels.h"

/*
 * Fonction qui crée une nouvelle zone de dessin
 * prend en paramètre la largeur et la hauteur de la zone
 * renvoie un pointeur vers cette zonne
 */
Area* create_area(unsigned int width, unsigned int height)
{
    Area* area=(Area *) malloc(sizeof(Area));
    area-> width = width;
    area->height = height;

    area->mat = (BOOL**) malloc(height * sizeof(BOOL*));

    for (int i = 0; i < height; i++)
    {
        area-> mat[i] =(BOOL**) malloc(width * sizeof(BOOL*));
    }
    area->nb_shape=0;
    return area;

}

/*
 * Fonction qui ajoute un forme a la zone de dessin
 * prend en paramètre la zone de dessin à modifier et la forme a ajouter
 */
void add_shape_to_area(Area* area,Shape* shape) {

        area->shapes[area->nb_shape] = shape;
        area->nb_shape++;
    }

/*
 * Efface la zonne de dessin en mettant a zero chaque pixel de la zone de dessin
 */
void clear_area(Area* area){
    for (int i = 0; i < area -> height; i++){
        for (int j = 0; j < area -> width; j++){
            area-> mat[i][j] = 0;
        }
    }
}
/*
 * Fonction qui supprime toutes les formes d'une zone de dessin mis en paramètre
 */
void erase_area(Area* area){
    for(int i=0;i< area->nb_shape;i++){
        delete_shape(area->shapes[i]);

    }
    area->nb_shape=0;

}

/*
 * Supprime (libere) la zone de dessin pris en paramètre
 */
void delete_area(Area* area){
    erase_area(area);
    for(int i=0; i<area->nb_shape;i++){
        free(area->mat[i]);
    }

    free(area);

    area=NULL;
}
/*
 * fonction qui dessine toutes les formes d'une zone de dessin
 * avec # si il y a un pixel et . si il y en a pas
 */
void draw_area(Area* area)
{
    int nb_pixels;
    for (int i = 0; i < area->nb_shape; i++) {

            Pixel **list_pixel = create_shape_to_pixel(area->shapes[i],&nb_pixels);
            for (int j = 0; j<nb_pixels; j++) {
                Pixel *pixel = list_pixel[j];
                if ((pixel->py-1 >= 0 && pixel->py-1 < area->height) && (pixel->px-1 >= 0 && pixel->px-1 < area->width)) {



                    area->mat[pixel->py-1][pixel->px-1] = 1;
                }
            }


    }


}

/*
 * fonction qui affiche une zone de dessin sur la console
 */
void print_area(Area* area) {
    for (int i = 0; i < area->height; i++) {
        for (int j = 0; j < area->width; j++) {

                if (area->mat[i][j] == 0) {
                    printf(" . ");
                }
                if (area->mat[i][j] == 1) {
                    printf(" # ");
                }

        }
        printf("\n");
    }
}

