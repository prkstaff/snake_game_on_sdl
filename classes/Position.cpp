#include "Position.h"

Position::Position(int sx, int sy, int sdirection):x(sx),y(sy),direction(sdirection){
};
int Position::get_x(){
    return x;
};
int Position::get_y(){
    return y;
};
