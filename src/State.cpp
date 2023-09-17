#include "State.h"
#include "Sound.h"
#include "Face.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"



// -----------Background assets -------------------
#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define BACKGROUND_SOUND_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_SOUND_LOOP_TIMES -1 // -1 for infinite loop
#define BACKGROUND_MUSIC_LOOP_TIMES -1 // -1 for infinite loop
#define BACKGROUND_MUSIC_PATH "assets/audio/stageState.ogg"

// -----------Enemy assets -------------------
#define ENEMY_SPRITE_PATH "assets/img/penguinface.png"
#define ENEMY_SOUND_PATH "assets/audio/boom.wav"

#define PI 3.141592

// -----------Tile assets -------------------
#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define MAP_TILEMAP_PATH "assets/map/tileMap.txt"
#define MAP_TILESET_PATH "assets/img/tileset.png"

State::State() {  
    
    // ====================Background ================================
    GameObject *background = new GameObject();
        Sprite *bg_sprite = new Sprite(*background, BACKGROUND_SPRITE_PATH);
        CameraFollower *bg_cmfl = new CameraFollower(*background);
        background->AddComponent((std::shared_ptr<Sprite>)bg_sprite);
        background->AddComponent((std::shared_ptr<CameraFollower>)bg_cmfl);
        
        background->box.x = 0;
        background->box.y = 0;
        objectArray.emplace_back(background);    // Adicionando o background no objectArray

    // ==================== Map ================================
    GameObject *map = new GameObject();
        TileSet *tileSet = new TileSet(*map, TILE_HEIGHT, TILE_WIDTH, MAP_TILESET_PATH);
        TileMap *tileMap = new TileMap(*map, MAP_TILEMAP_PATH, tileSet);
        tileMap->SetParallax(0.1);
        map->AddComponent((std::shared_ptr<TileMap>)tileMap);
        
        map->box.x = 0;
        map->box.y = 0;
        objectArray.emplace_back(map);

    quitRequested = false;
    LoadAssets();
    music.Play(BACKGROUND_MUSIC_LOOP_TIMES);
}

State::~State(){objectArray.clear();}

//método que cuida de pré-carregar os assets do state do jogo
void State::LoadAssets(){
    music.Open(BACKGROUND_MUSIC_PATH);
}


//atualização do estado das entidades, testes de
//colisões e a checagem relativa ao encerramento do jogo.
void State::Update(float dt){
    InputManager& input = InputManager::GetInstance();
       
    Camera::Update(dt);

    // Se o evento for quit, setar a flag para terminação
    if ((input.KeyPress(ESCAPE_KEY)) || input.QuitRequested()){
        quitRequested = true;
    }

     // Se o evento for clique...(SPACEBAR)
    if (input.KeyPress(SPACEBAR_KEY)){
        //Vec2 objPos = Vec2(200, 0);
        //objPos.GetRotated(-PI + PI * (rand() % 1001) / 500.0);
        //objPos = objPos + Vec2(input.GetMouseX(), input.GetMouseY());
        Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(input.GetMouseX(), input.GetMouseY());
        AddObject((int)objPos.x - Camera::pos.x, (int)objPos.y - Camera::pos.y);
        std::cout << "aaaaaaaa: " << (int)objPos.x - Camera::pos.x << " "<< Camera::pos.y<< std::endl;
    }

    for (int i = (int)objectArray.size() - 1; i >= 0; --i){
        objectArray[i]->Update(dt);         
    }
    for (int i = (int)objectArray.size() - 1; i >= 0; --i){
        if (objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
        }
    }

    SDL_Delay(dt);
}


//renderização do estado do jogo. Isso inclui entidades, cenários, HUD, entre outros.
void State::Render(){
    for (int i = 0; i != (int)objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {return quitRequested;}



void State::AddObject(int mouseX, int mouseY){
    GameObject *enemy = new GameObject();
        Sprite *enemy_sprite = new Sprite(*enemy, ENEMY_SPRITE_PATH);
        Sound *enemy_sound = new Sound(*enemy, ENEMY_SOUND_PATH);
        enemy->AddComponent((std::shared_ptr<Sound>)enemy_sound);
        enemy->AddComponent((std::shared_ptr<Sprite>)enemy_sprite);

        Face *enemy_interface = new Face(*enemy);
        enemy->AddComponent((std::shared_ptr<Face>)enemy_interface);
        
        //-enemy_sprite->GetHeight() / 2 para ser o centro do sprite a posicao
        enemy->box.x = mouseX - enemy_sprite->GetWidth() / 2; 
        enemy->box.y = mouseY - enemy_sprite->GetHeight() / 2 ;
        

    std::cout << "Object created box: " << "x:" << enemy -> box.x << " " <<
                                           "y:" << enemy -> box.y << " " <<
                                           "w:" << enemy -> box.w << " " << 
                                           "h:" << enemy -> box.h << std::endl;
    // Adicionando o inimigo no objectArray
    objectArray.emplace_back(enemy);
}