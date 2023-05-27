//
// Created by koco on 17/04/2023.
//

#include "id.h"
unsigned int global_id=0;
/*
 * Fonction qui permet d'augmenter l'id a chaque fois qu'une forme est rajouté
 */
unsigned int get_next_id(){
    return global_id++;
}