#include "Vec2.h"
#include <math.h>

Vec2::Vec2(int x, int y){
    this->x = x;
	this->y = y;
}

Vec2::Vec2() : Vec2(0, 0)
{
}

Vec2 Vec2::operator+(const Vec2 &other) const{
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::GetRotated(float value){   
    //rotação horária.
    int xline, yline;
    xline = (x * cos(value)) - (y * sin(value));
    yline = (y * cos(value)) + (x * sin(value));
    return Vec2(xline, yline);
}