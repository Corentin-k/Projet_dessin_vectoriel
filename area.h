//
// Created by koco on 25/04/2023.
//

#ifndef PROJET_C_AREA_H
#define PROJET_C_AREA_H
#include "shape.h"


#define SHAPE_MAX 100 //Nombremaximumdeformes
#define BOOL int
struct area{
    unsigned int width;//Nombre de pixels en largeur ou nombre de colonnes(axe y)
    unsigned int height;//Nombre de pixels en hauteur ou nombre de lignes (axe x)
    BOOL** mat; //Matrice des pixels de taille (width*height)
    Shape* shapes[SHAPE_MAX]; //Tableau des formes;
    int nb_shape;//Nombre de formes dans le tableau shapes(taillelogique) }; typedefstructareaArea;
};
typedef struct area Area;

Area* create_area(unsigned int width,unsigned int height);
void add_shape_to_area(Area* area,Shape* shape);
void clear_area(Area* area);
void erase_area(Area* area);
void delete_area(Area* area);
void draw_area(Area* area);
void print_area(Area* area);

#endif //PROJET_C_AREA_H
