#ifndef _COMMAND_
#define _COMMAND_
#include <iostream>
#include "Snake.h"

class Command{
    public:
        virtual ~Command(){};
        virtual void execute(Snake* snake) = 0;
};
class GoDown: public Command{
    void execute(Snake* snake);
};
class GoUp: public Command{
    void execute(Snake* snake);
};
class GoLeft: public Command{
    void execute(Snake* snake);
};
class GoRight: public Command{
    void execute(Snake* snake);
};
#endif /* ifndef _COMMAND_
class Command{

}; */

