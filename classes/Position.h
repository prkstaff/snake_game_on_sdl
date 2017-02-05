#ifndef _Position_
#define _Position_
#include <stdio.h>

class Position{
    private:
        const int x;
        const int y;
        const int direction;
    public:
        int get_x();
        int get_y();
        int get_direction();
        Position(int sx, int sy , int sdirection);
};
#endif /* ifndef _Position_ */
