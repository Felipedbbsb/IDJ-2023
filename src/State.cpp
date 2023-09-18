#include "State.h"


State::State() {  
    started = false;
    quitRequested = false;

    // ====================Background ================================
    GameObject *background = new GameObject();
        Sprite *bg_sprite = new Sprite(*background, BG_SPRITE);
        CameraFollower *bg_cmfl = new CameraFollower(*background);
        background->AddComponent((std::shared_ptr<Sprite>)bg_sprite);
        background->AddComponent((std::shared_ptr<CameraFollower>)bg_cmfl);
        
        background->box.x = 0;
        background->box.y = 0;
        objectArray.emplace_back(background);    // Adicionando o background no objectArray

    // ==================== Map ================================
    GameObject *map = new GameObject();
        TileSet *tileSet = new TileSet(*map, TILE_H, TILE_W, MAP_TILESET);
        TileMap *tileMap = new TileMap(*map, MAP_TILEMAP, tileSet);
        tileMap->SetParallax(0.005);
        map->AddComponent((std::shared_ptr<TileMap>)tileMap);
        
        map->box.x = 0;
        map->box.y = 0;
        objectArray.emplace_back(map);

    
    LoadAssets();
    music.Open(BG_MUSIC);
    music.Play(BACKGROUND_MUSIC_LOOP_TIMES);
}

State::~State(){objectArray.clear();}

//método que cuida de pré-carregar os assets do state do jogo
void State::LoadAssets(){
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

void State::Start(){
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}


std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    std::shared_ptr<GameObject> tmp(go);
    objectArray.push_back(tmp);
    if (started){tmp->Start();}
    std::weak_ptr<GameObject> created_go(tmp);
    return created_go;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go){
    for (int i = 0; i < (int)objectArray.size(); i++){
        if (go == objectArray[i].get()){
            std::weak_ptr<GameObject> created_go(objectArray[i]);
            return created_go;
        }
    }
    std::weak_ptr<GameObject> empty_go;
    return empty_go;
}