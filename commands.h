//
// Created by koco on 15/05/2023.
//

#ifndef PROJET_C_COMMANDS_H
#define PROJET_C_COMMANDS_H
#include "area.h"
struct command {
    char name[50];
    int int_size;
    int int_params[10];
    int str_size;
    char* str_params[10];
};
enum CommandName {
    point,
    line,
    square,
    rectangle,
    circle,
    polygon,
    clear,
    quit,
    plot,
    list,
    delete,
    erase,
    help,
    error,
};
typedef struct command Command;
Command* create_command();

void add_str_param(Command* cmd,  char* p);
void add_int_param(Command* cmd, int p);
void free_cmd(Command* cmd);
int read_exec_command(Command* cmd,Area*area);
void read_from_stdin(Command* cmd);

void afficher_formes(Area* area);
#endif //PROJET_C_COMMANDS_H
