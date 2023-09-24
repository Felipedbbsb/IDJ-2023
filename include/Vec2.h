#pragma once

#include <memory>
#include <iostream>
#include <math.h>
class Vec2{
    public:
        Vec2(float x, float y);
        Vec2();
        static Vec2 D2points(Vec2 begin, Vec2 end);
        float Hypotenuse();
        Vec2 GetRotated(float theta);
        void Rotate(float theta);
        void RotateAngle(float degrees);
        float RotateDegree();
        float x, y;
        Vec2 operator+(const Vec2 &other) const;
        Vec2 operator-(const Vec2 &other) const;
};