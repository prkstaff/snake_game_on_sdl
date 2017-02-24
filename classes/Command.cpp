#include "Command.h"
#include <iostream>

void GoUp::execute(){
    printf("Pressed up");
}
void GoDown::execute(){
    printf("Pressed Down");
}
void GoLeft::execute(){
    printf("Pressed Left");
}
void GoRight::execute(){
    printf("Pressed Right");
}
void Pause::execute(){
    printf("Pressed Pause");
}
