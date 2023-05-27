//
// Created by koco on 13/04/2023.
//

#include "formes.h"
#include <stdio.h>
#include <stdlib.h>


Point *create_point(int px, int py){
    Point* p=malloc(sizeof(Point));
    p->pos_x=px;
    p->pos_y=py;
    return p;
}
void delete_point(Point * point){
    free(point);
    point=NULL;
}
void print_point(Point * p){
    printf("POINT %d %d\n",p->pos_x,p->pos_y);
}



Line *create_line(Point * p1, Point * p2){
    Line* line=malloc(sizeof(Line));
    line->p1=p1;
    line->p2=p2;
    return line;
}
void delete_line(Line * line){
    free(line ->p1);
    free(line ->p2);
    free(line);
    line=NULL;

}
void print_line(Line * line){
    printf("LINE %d %d %d %d\n",line->p1->pos_x,line->p1->pos_y,line->p2->pos_x,line->p2->pos_y);
}



Square *create_square(Point * point, int length){
    Square* square=malloc(sizeof(Square));
    square->p=point;
    square->length=length;
    return square;
}
void delete_square(Square * square){
    free(square -> p);
    free(square);
    square=NULL;
}
void print_square(Square * square){
    printf("CARRE (%d %d), (%d %d), (%d %d), (%d %d)\n",
           square->p->pos_x,square->p->pos_y,
           square->p->pos_x,((square->p->pos_y)+(square->length)),
           square->p->pos_x+square->length,square->p->pos_y,
           square->p->pos_x+square->length,square->p->pos_y+square->length);
}



Rectangle* create_rectangle(Point * point, int width, int height){
    Rectangle * rectangle=malloc(sizeof(Rectangle));
    rectangle->p=point;
    rectangle->width=width;
    rectangle->height=height;
    return  rectangle;
}
void delete_rectangle(Rectangle * rectangle){
    free(rectangle->p);
    free(rectangle);
    rectangle=NULL;
}
void print_rectangle(Rectangle * rectangle){
    printf("Rectangle (%d %d), (%d %d), (%d %d), (%d %d)\n",
           rectangle->p->pos_x,rectangle->p->pos_y,
           rectangle->p->pos_x,((rectangle->p->pos_y)+(rectangle->width)),
           rectangle->p->pos_x+rectangle->height,rectangle->p->pos_y,
           rectangle->p->pos_x+rectangle->height,rectangle->p->pos_y+rectangle->width);
}



Circle *create_circle(Point * center, int radius){
    Circle * circle=malloc(sizeof(Circle));
    circle->center=center;
    circle->radius=radius;
    return circle;
}
void delete_circle(Circle * circle){
    free(circle->center);
    free(circle);
    circle=NULL;
}
void print_circle(Circle * circle){
    printf("CIRCLE (%d %d),%d\n", circle->center->pos_x,circle->center->pos_y, circle->radius);
}



Polygon *create_polygon(int n){
    Polygon * polygon=malloc(sizeof(Polygon));
    polygon->n=n+1;
    polygon->points = malloc((n+1) * sizeof(Point*));
    for(int i=0;i<n;i++){
        int x=0,y;
        printf("Position x et Position y point %d : ",i+1);
        scanf(" %d %d",&x,&y);
        polygon->points[i]=create_point(x,y);
        printf("\n");
    }
    polygon->points[n]= create_point(polygon->points[0]->pos_x,polygon->points[0]->pos_y);
    return polygon;
}
void delete_polygon(Polygon * polygon){
    free(polygon->points);
    free(polygon);
    polygon=NULL;
}
void print_polygon(Polygon * polygon){
    printf("POLYGON taille= %d, points=",polygon->n);
    for(int i=0;i<polygon->n;i++){
        printf(" (%d %d)", polygon->points[i]->pos_x,polygon->points[i]->pos_y);
    }
}





