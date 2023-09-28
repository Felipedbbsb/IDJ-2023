#pragma once

#include <vector>
#include <memory>

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Face.h"
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


// -----------Background assets -------------------
#define BG_SPRITE "assets/img/ocean.jpg"
#define BG_SOUND "assets/audio/stageState.ogg"
#define BACKGROUND_SOUND_LOOP_TIMES -1 // -1 for infinite loop
#define BACKGROUND_MUSIC_LOOP_TIMES -1 // -1 for infinite loop
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
class State {
    public:
        State();
        ~State();
        bool QuitRequested();   
        void Start();                                    

        void LoadAssets();
        void Update(float dt);
        void Render();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    private:
        Music music;
        bool quitRequested;
        bool started;
        std::vector<std::shared_ptr<GameObject>> objectArray;
};