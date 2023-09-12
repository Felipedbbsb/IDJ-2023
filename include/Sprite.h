#pragma once


#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include <iostream>
#include "SDL_include.h"
#include "Component.h"

//Class responsible for load and render of images
class Sprite : public Component
{
public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, std::string file);
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y,
               int w, int h);
  void Render();
  void Render(int x, int y);
  int GetWidth();
  int GetHeight();
  bool IsOpen();
  void Update(float dt);
  bool Is(std::string type);

private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;
};