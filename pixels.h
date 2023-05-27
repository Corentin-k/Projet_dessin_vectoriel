//
// Created by koco on 15/05/2023.
//

#ifndef PROJET_C_PIXELS_H
#define PROJET_C_PIXELS_H
#include "formes.h"
#include "Shape.h"
struct pixel {
    unsigned int px;
    unsigned int py;
};
typedef struct pixel Pixel;
Pixel * create_pixel(unsigned int px, unsigned int py);
int min (int a,int b);
int max (int a,int b);

void delete_pixel(Pixel * pixel);

void pixel_point(Point* point, Pixel*** pixel, int* nb_pixels);
void pixel_line(Line* line, Pixel*** pixel, int* nb_pixels);
void pixel_square(Square * square, Pixel*** pixel, int* nb_pixels);
void pixel_rectangle(Rectangle * rectangle, Pixel*** pixel, int* nb_pixels);
void pixel_circle(Circle * circle, Pixel*** pixel, int* nb_pixels);
void pixel_polygon(Polygon * polygon, Pixel*** pixel, int* nb_pixels);


Pixel** create_shape_to_pixel(Shape * shape, int* nb_pixels);
#endif //PROJET_C_PIXELS_H
