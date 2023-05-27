//
// Created by koco on 15/05/2023.
//

#include "pixels.h"
#include "formes.h"
#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
/*
 * Fonction qui permet d’allouer un espace mémoire de type Pixel,
 * de l’initialiser et
 * de retourner l’adresse de l’espace mémoire alloué.
 */
Pixel *create_pixel(unsigned int px,unsigned int py){
    Pixel * p = (Pixel *)malloc(sizeof (Pixel));
    p ->px = px;
    p ->py = py;
    return p;
}
/*
 * Fonction qui permet de libérer l’espace mémoire alloué par
 * la fonction précédente.
 */
void delete_pixel(Pixel *pixel) {
    free(pixel);
    pixel=NULL;
}

/*
 * Fonction qui permet d'allouer dynamicquement l'espace mémoire pour
 * pixel et creer le pixel en fonction de la forme point
 */
void pixel_point(Point* pt, Pixel*** pixel, int* nb_pixels)
{
    *nb_pixels   = 1;
    *pixel= (Pixel**) malloc (*nb_pixels*sizeof (Pixel*));
    (*pixel)[0] = create_pixel(pt->pos_x, pt->pos_y);

}

/*
 * Fonction qui calcul le minimum entre deux valeur
 * pour la fonction pixel_line
 */
int min (int a,int b)
{
    if (a < 0 && b < 0)
    {
        a = a * (-1);
        b = b * (-1);
        if (a < b)
        {
            return a;
        }
        else return b;
    }
    if (a > 0 && b < 0)
    {
        b = b * (-1);
        if (a < b)
        {
            return a;
        }
        else return b;
    }
    if (a < 0 && b > 0)
    {
        a = a * (-1);
        if (a < b)
        {
            return a;
        }
        else return b;
    }
    return a;

}
/*
 * Fonction qui calcul le maximum entre deux valeur
 * pour la fonction pixel_line
 */
int max (int a,int b)
{
    if (a < 0 && b < 0)
    {
        a = a * (-1);
        b = b * (-1);
        if (a > b)
        {
            return a;
        }
        else return b;
    }
    if (a > 0 && b < 0)
    {
        b = b * (-1);
        if (a > b)
        {
            return a;
        }
        else return b;
    }
    if (a < 0 && b > 0)
    {
        a = a * (-1);
        if (a > b)
        {
            return a;
        }
        else return b;
    }
    return a;
}

/*
 * Fonction qui permet de calculer la positon des pixels que va occuper une ligne
 * en fonction de la forme Line et utilise l'algorithme de Nicolas Flasque
 */
void pixel_line(Line* line, Pixel*** pixel, int* nb_pixels)
{
    if (line->p1->pos_x>line->p2->pos_x){
        int tempx=line->p1->pos_x,tempy=line->p1->pos_y;
        line->p1->pos_x=line->p2->pos_x;
        line->p1->pos_y=line->p2->pos_y;
        line->p2->pos_x=tempx;
        line->p2->pos_y=tempy;
    }
    int dx, dy, dmin,dmax, nb_segs, taille_base, restants;

    dy = ((line ->p2 ->pos_y) - (line ->p1->pos_y));
    dx = (line ->p2 ->pos_x) - (line ->p1->pos_x);
    dmin = min(dx,dy);
    dmax = max (dx, dy);
    nb_segs = dmin + 1;
    taille_base = (dmax+1)/nb_segs;

    Pixel *px = NULL;
    int segments [nb_segs];
    for (int i = 0; i < nb_segs; i++) {
        segments[i] = taille_base;
    }
    restants = (dmax +1)%(dmin +1);
    // Pixels à répartir
    int *cumuls = (int *)malloc(nb_segs*sizeof(int));
    cumuls[0]=0;

    for (int i = 1; i < nb_segs;i++)
    {
        cumuls[i] = (((i+1)*restants)%(dmin+1) < (i*restants)%(dmin+1));
        segments[i] = segments[i]+cumuls[i];

    }
    int yA = line->p1->pos_y;
    int xA = line->p1->pos_x;


    segments[0] = segments[0]-1;
    int k = 0;
    // Regarde si tous les points sont aligner sur l'axe y = ligne verticale
    if (dx == 0) { // Ligne verticale
        *nb_pixels = abs(dy)+1;
        *pixel = (Pixel**) malloc( *nb_pixels* sizeof(Pixel*));
        px = create_pixel(xA, yA);
        (*pixel)[k++] = px;
        for (int i = 0; i < abs(dy); i++) {
            if (line->p1->pos_y > line->p2->pos_y) {
                yA--;
            } else {
                yA++;
            }
            px = create_pixel(xA, yA);
            (*pixel)[k++] = px;

        }
    // Regarde si tous les points sont aligner sur l'axe x = ligne horizontale
    } else if (dy == 0) { // Ligne horizontale
        *nb_pixels = abs(dx)+1;
        *pixel = (Pixel**) malloc(*nb_pixels * sizeof(Pixel*));
        px = create_pixel(xA, yA);
        (*pixel)[k++] = px;
        for (int i = 0; i < abs(dx); i++) {
            if (line->p1->pos_x > line->p2->pos_x) {
                xA--;
            } else {
                xA++;
            }
            px = create_pixel(xA, yA);
            (*pixel)[k++] = px;

        }
    }else{ // si non creer une ligne selon l'algo de Nicolas Flasque
        *nb_pixels = dmax + 1;
        *pixel = (Pixel**) malloc(*nb_pixels * sizeof(Pixel*));
        px = create_pixel(xA, yA);
        (*pixel)[k++] = px;
        for (int i = 0; i < nb_segs; i++) {

            for (int j = 0; j < segments[i]; j++) {

                if (dy < 0) { // On trace vers le bas
                    if (dx > abs(dy)) { // Segments horizontaux
                        xA += 1;
                    } else { // Segments verticaux
                        yA -= 1;
                    }
                } else { // On trace vers le haut
                    if (dx > dy) { // Segments horizontaux
                        xA += 1;
                    } else { // Segments verticaux
                        yA += 1;
                    }
                }
                px = create_pixel(xA, yA);
                (*pixel)[k++] = px;
            }
            if (dy < 0) { // On trace vers le bas
                if (dx > abs(dy)) { // Segments horizontaux
                    yA -= 1;
                } else { // Segments verticaux
                    xA += 1;
                }
            } else { // On trace vers le haut
                if (dx > dy) { // Segments horizontaux
                    yA += 1;
                } else { // Segments verticaux
                    xA += 1;
                }
            }
        }
    }
}
/*
 * Fonction qui permet de calculer la positon des pixels que va occuper un carré
 * en fonction de la forme square et utilise la fonction pixel_line
 */

void pixel_square(Square * square, Pixel*** pixel, int* nb_pixels){
    int l=square->length;
    int x_min = square->p->pos_x;
    int x_max = square->p->pos_x + l - 1;
    int y_min = square->p->pos_y;
    int y_max =square->p->pos_y + l - 1;

    *nb_pixels = (l * 2) + ((l - 2) * 2);
    *pixel = (Pixel**)malloc(*nb_pixels * sizeof(Pixel*));

    int k = 0;
    for (int i = x_min; i <= x_max; i++) {
        Pixel* px = create_pixel(i, y_min);
        (*pixel)[k++] = px;
    }
    for (int i = y_min + 1; i <= y_max - 1; i++) {
        Pixel* px = create_pixel(x_max, i);
        (*pixel)[k++] = px;
    }
    for (int i = x_max; i >= x_min; i--) {
        Pixel* px = create_pixel(i, y_max);
        (*pixel)[k++] = px;
    }
    for (int i = y_max - 1; i >= y_min + 1; i--) {
        Pixel* px = create_pixel(x_min, i);
        (*pixel)[k++] = px;
    }
}

/*
 * Fonction qui permet de calculer la positon des pixels que va occuper un rectangle
 * en fonction de la forme rectangle et utilise la fonction pixel_line
 */
void pixel_rectangle(Rectangle * rectangle, Pixel*** pixel, int* nb_pixels){
    int longueur= rectangle->width;
    int largeur= rectangle->height;
    int x_min = rectangle->p->pos_x;
    int x_max = rectangle->p->pos_x + longueur - 1;
    int y_min = rectangle->p->pos_y;
    int y_max = rectangle->p->pos_y + largeur - 1;

    *nb_pixels = (longueur * 2) + (largeur * 2) - 4;
    *pixel = (Pixel**)malloc(*nb_pixels * sizeof(Pixel*));

    int k = 0;
    for (int i = x_min; i <= x_max; i++) {
        Pixel* px = create_pixel(i, y_min);
        (*pixel)[k++] = px;
    }
    for (int i = y_min + 1; i <= y_max - 1; i++) {
        Pixel* px = create_pixel(x_max, i);
        (*pixel)[k++] = px;
    }
    for (int i = x_max; i >= x_min; i--) {
        Pixel* px = create_pixel(i, y_max);
        (*pixel)[k++] = px;
    }
    for (int i = y_max - 1; i >= y_min + 1; i--) {
        Pixel* px = create_pixel(x_min, i);
        (*pixel)[k++] = px;
    }
}
/*
 * Fonction qui permet de calculer la positon des pixels que va occuper un polygon
 * en fonction de la forme polygon et utilise la fonction pixel_line
 */
void pixel_polygon(Polygon * polygon, Pixel*** pixel, int* nb_pixels) {
    int k=0; // calcul de la mémoire
    for (int i = 0; i < polygon->n - 1; i++) {
        int x1 = polygon->points[i]->pos_x;
        int y1 = polygon->points[i]->pos_y;
        int x2 = polygon->points[i+1]->pos_x;
        int y2 = polygon->points[i+1]->pos_y;

        Pixel** line_pixels;
        int nb_line_pixels;
        Shape* l=create_line_shape(x1,y1,x2,y2);
        pixel_line(l->ptrShape,&line_pixels,&nb_line_pixels);
        for (int j = 0; j < nb_line_pixels; j++) {
            k++;
        }
        free(line_pixels);
        free(l);
    }

    *nb_pixels =k;
    *pixel = (Pixel**)malloc(*nb_pixels * sizeof(Pixel*));
    k = 0;
   
    for (int i = 0; i < polygon->n - 1; i++) {
        int x1 = polygon->points[i]->pos_x;
        int y1 = polygon->points[i]->pos_y;
        int x2 = polygon->points[i+1]->pos_x;
        int y2 = polygon->points[i+1]->pos_y;

        Pixel** line_pixels;
        int nb_line_pixels;
        Shape* l=create_line_shape(x1,y1,x2,y2);
        pixel_line(l->ptrShape,&line_pixels,&nb_line_pixels);

        for (int j = 0; j < nb_line_pixels; j++) {
            (*pixel)[k++] = (line_pixels)[j];
        }

        free(line_pixels);
        free(l);
    }
}


/*
 * Fonction qui permet de calculer la positon des pixels que va occuper un cerlce
 * en fonction de la forme Circle et utilise l'algorithme de tracé de cercle d’Andres.
 */
void pixel_circle(Circle* circle, Pixel*** pixel, int *nb_pixels) {
    int x = 0;
    int y = circle->radius;
    int d =  circle->radius-1;
    int k = 0;// nombre d’éléments dans le tableau de pixels tab
    Pixel *px = NULL;
    // Calcul du nombre d'éléments pour allouer pixel
    while (y >= x) {
        k=k+8;
        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        }
        else if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        }
        else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }

    *nb_pixels   = k;

    *pixel= (Pixel**) malloc (*nb_pixels*sizeof (Pixel*));
    x = 0;
    y = circle->radius;
    d =  circle->radius-1;
    k = 0;
    while (y >= x) {
        //creation des 8 octans
        px = create_pixel(circle->center->pos_x + x, circle->center->pos_y + y);
        (*pixel)[k++] = px;
        px = create_pixel(circle->center->pos_x + y, circle->center->pos_y + x);
        (*pixel)[k++] = px;

        px = create_pixel(circle->center->pos_x +y, circle->center->pos_y-x);
        (*pixel)[k++] = px;
        px = create_pixel(circle->center->pos_x +x, circle->center->pos_y -y);
        (*pixel)[k++] = px;

        px = create_pixel(circle->center->pos_x - x, circle->center->pos_y- y);
        (*pixel)[k++] = px;

        px = create_pixel(circle->center->pos_x -y, circle->center->pos_y - x);
        (*pixel)[k++] = px;

        px = create_pixel(circle->center->pos_x - y, circle->center->pos_y +x);
        (*pixel)[k++] = px;

        px = create_pixel(circle->center->pos_x - x, circle->center->pos_y + y);
        (*pixel)[k++] = px;

        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        }
        else if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        }
        else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }
}

/*
 * Fonction qui permet de transformer une forme quelconque en un ensemble de pixels
 * prend en paramètre une forme shape et renvoie un double pointeur vers le tableau de pixel
 */
Pixel** create_shape_to_pixel(Shape * shape, int* nb_pixels) {
    Pixel **pixel = NULL;
    switch (shape->shape_type) {
        case POINT:
            pixel_point(shape->ptrShape, &pixel, nb_pixels);
            break;
        case LINE:
            pixel_line(shape->ptrShape, &pixel, nb_pixels);
            break;
        case SQUARE:
            pixel_square(shape->ptrShape, &pixel, nb_pixels);
            break;
        case RECTANGLE:
            pixel_rectangle(shape->ptrShape,&pixel, nb_pixels);
            break;
        case CIRCLE:
            pixel_circle(shape->ptrShape, &pixel, nb_pixels);
            break;
        case POLYGON:
            pixel_polygon(shape->ptrShape, &pixel, nb_pixels);
            break;
    }
    return pixel;
}




