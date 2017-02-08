#ifndef _Position_
#define _Position_
#include <stdio.h>

class Position{
    private:
        int x;
        int y;
        int direction;
    public:
        int get_x();
        int get_y();
        int get_direction();
        void set_x_y(int sx, int sy);
        Position(int sx, int sy , int sdirection);
};
#endif /* ifndef _Position_ */
