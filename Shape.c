//
// Created by koco on 13/04/2023.
//

#include "Shape.h"
#include <stdio.h>
#include <stdlib.h>
#include "formes.h"
#include "id.h"

Shape *create_empty_shape(SHAPE_TYPE shape_type) {
    Shape *shp = (Shape *) malloc(sizeof(Shape));
    shp->ptrShape = NULL;
    shp->id = get_next_id();
    shp->shape_type = shape_type;
    return shp;
}

Shape *create_point_shape(int px, int py) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(px, py);
    shp->ptrShape = p;
    return shp;
}


Shape *create_line_shape(int px1, int py1, int px2, int py2) {
    Shape *shp = create_empty_shape(LINE);
    Point *p1 = create_point(px1, py1);
    Point *p2 = create_point(px2, py2);
    Line *l = create_line(p1,p2);
    shp->ptrShape = l;
    return shp;
}

Shape *create_square_shape(int px, int py, int length) {
    Shape *shp = create_empty_shape(SQUARE);
    Point *p = create_point(px, py);
    Square *sq = create_square(p, length);
    shp->ptrShape = sq;
    return shp;
}
Shape *create_rectangle_shape(int px, int py, int width, int height) {
    Shape *shp = create_empty_shape(RECTANGLE);
    Point *p = create_point(px, py);
    Rectangle *r = create_rectangle(p, width, height);
    shp->ptrShape = r;
    return shp;
}

Shape *create_circle_shape(int px, int py, int radius) {
    Shape *shp = create_empty_shape(CIRCLE);
    Point *p = create_point(px, py);
    Circle *c = create_circle(p, radius);
    shp->ptrShape = c;
    return shp;
}
Shape *create_polygon_shape(int lst[], int n){
    Shape *shp = create_empty_shape(POLYGON);
    Polygon *polygon= create_polygon(n);
    shp->ptrShape = polygon;
    return shp;
}
void delete_shape(Shape * shape){


    switch (shape->shape_type) {
        case POINT:
            delete_point(shape->ptrShape);
            free(shape);
            shape=NULL;
            break;
        case LINE:
            delete_line(shape->ptrShape);
            free(shape);
            shape=NULL;
            break;
        case SQUARE:
            delete_square(shape->ptrShape);
            free(shape);
            shape=NULL;
            break;
        case RECTANGLE:
            delete_rectangle(shape->ptrShape);
            free(shape);
            shape=NULL;
            break;
        case CIRCLE:
            delete_circle(shape->ptrShape);
            free(shape);
            shape=NULL;
            break;
        case POLYGON:
            delete_polygon(shape->ptrShape);
            free(shape);
            shape=NULL;
            break;

    }


}
void print_shape(Shape * shape){
    switch (shape->shape_type) {
        case POINT:
            print_point(shape->ptrShape);
            break;
        case LINE:
            print_line(shape->ptrShape);
            break;
        case SQUARE:
            print_square(shape->ptrShape);
            break;
        case RECTANGLE:
            print_rectangle(shape->ptrShape);
            break;
        case CIRCLE:
            print_circle(shape->ptrShape);
            break;
        case POLYGON:
            print_polygon(shape->ptrShape);
            break;

    }

}



