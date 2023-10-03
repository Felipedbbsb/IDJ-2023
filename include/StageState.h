#pragma once

#include <vector>
#include <memory>

#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "GameObject.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Collision.h"

// -----------Background assets -------------------
#define BG_SPRITE "assets/img/ocean.jpg"
#define BG_SOUND "assets/audio/stageState.ogg"
#define BACKGROUND_SOUND_LOOP_TIMES -1 // -1 for infinite loop
#define BG_MUSIC_LOOP -1 // -1 for infinite loop
#define BG_MUSIC "assets/audio/stageState.ogg"

// -----------Enemy assets -------------------
#define ENEMY_SPRITE "assets/img/penguinface.png"
#define ENEMY_SOUND "assets/audio/boom.wav"

#define PI 3.141592

// -----------Tile assets -------------------
#define TILE_W 64
#define TILE_H 64
#define MAP_TILEMAP "assets/map/tileMap.txt"
#define MAP_TILESET "assets/img/tileset.png"


//Class responsible for control of state
class StageState  : public State{
    public:
        StageState();
        ~StageState();                          

        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();

    private:
        Music music;
        TileSet* tileSet;

};