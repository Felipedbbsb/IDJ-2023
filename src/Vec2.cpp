#include "Vec2.h"
#include <math.h>

Vec2::Vec2(float x, float y){
    this->x = x;
	this->y = y;
}

Vec2::Vec2() : Vec2(0, 0)
{}

Vec2 Vec2::operator+(const Vec2 &other) const{
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(x - other.x, y - other.y);
}

void Vec2::Rotate(float value){   
    //rotação horária.
    float xline, yline;
    xline = (x * cos(value)) - (y * sin(value));
    yline = (y * cos(value)) + (x * sin(value));
    x = xline;
    y = yline;
}


void Vec2::RotateDeg(float theta)
{
    // Receives theta in degrees
    Rotate(theta / (180 / 3.14159265359));
}

Vec2 Vec2::GetRotated(float theta)
{   
    Vec2 temp(x, y);
    temp.Rotate(theta);

    return temp;
}

Vec2 Vec2::GetRotatedDeg(float theta)
{
    Vec2 temp(x, y);
    temp.RotateDeg(theta);

    return temp;
}



float Vec2::Arg()
{
    return atan2(y, x);
}

float Vec2::ArgDeg()
{   
    // Return value in degrees
    float argDeg = Arg() * (180 / 3.14159265359);
    return argDeg;
}

float Vec2::Magnitude()
{
    return (float)sqrt(pow(x, 2) + pow(y, 2));
}

//distancia entre A(inicial) e B, neste caso ficar negativo é ideal
Vec2 Vec2::D2points(Vec2 begin, Vec2 end)
{
    float x_distance = end.x - begin.x;
    float y_distance = end.y - begin.y;

    return Vec2(x_distance, y_distance);
}
