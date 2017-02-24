#include "Command.h"
#include <iostream>
#include "Game.h"

void GoUp::execute(Snake* snake){
    snake->set_direction(UP);
}
void GoDown::execute(Snake* snake){
    snake->set_direction(DOWN);
}
void GoLeft::execute(Snake* snake){
    snake->set_direction(LEFT);
}
void GoRight::execute(Snake* snake){
    snake->set_direction(RIGHT);
}
