#ifndef _COMMAND_
#define _COMMAND_
#include <iostream>

class Command{
    public:
        virtual ~Command(){};
        virtual void execute() = 0;
};
class GoDown: public Command{
    void execute();
};
class GoUp: public Command{
    void execute();
};
class GoLeft: public Command{
    void execute();
};
class GoRight: public Command{
    void execute();
};
class Pause: public Command{
    void execute();
};

#endif /* ifndef _COMMAND_
class Command{

}; */

