#pragma once

#include <memory>
#include <iostream>
#include "Vec2.h"

class Rect {
    public:
      Rect(float x, float y, float w, float h);
      bool Contains(float x, float y);
      float x = 0, y = 0, w = 0, h = 0;
      void DefineCenter(float x, float y);
      void DefineCenter(Vec2 box);
      Vec2 GetCenter();

};           