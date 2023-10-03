#include "StageState.h"

StageState::StageState() : State::State(){  
    
    
    // ====================Background ================================
    GameObject *background = new GameObject();
        Sprite *bg_sprite = new Sprite(*background, BG_SPRITE);
        CameraFollower *bg_cmfl = new CameraFollower(*background);
        background->AddComponent((std::shared_ptr<Sprite>)bg_sprite);
        background->AddComponent((std::shared_ptr<CameraFollower>)bg_cmfl);
        
        AddObject(background);

    // ==================== Map ================================
    GameObject *map = new GameObject();
        TileSet *tileSet = new TileSet(*map, TILE_H, TILE_W, MAP_TILESET);
        TileMap *tileMap = new TileMap(*map, MAP_TILEMAP, tileSet);
        tileMap->SetParallax(0.01);
        map->AddComponent((std::shared_ptr<TileMap>)tileMap);

        AddObject(map);

    // =====================PENGUIN ============================
    GameObject *penguinBody = new GameObject(704, 640);
        PenguinBody* penguinBody_behaviour = new PenguinBody(*penguinBody);
        penguinBody->AddComponent((std::shared_ptr<PenguinBody>)penguinBody_behaviour);
       
        AddObject(penguinBody);

    // ===================== ALIEN  ===============================
     for (int i = 0; i < 3 + (rand() % 3) ; i++){ //min 3 and max 6 aliens
        GameObject *alien = new GameObject();
            int randomMinions = 2 + (rand() % 4); // Minimum of 2 and maximum of 6 minions
            Alien *behaviour = new Alien(*alien, randomMinions);
            alien->AddComponent((std::shared_ptr<Alien>)behaviour);

            alien->box.x = (rand() % 1000) ;
            alien->box.y = (rand() % 1000);

            AddObject(alien);

    }

    music.Open(BG_MUSIC);
}

//Agora se reseta a posicao da camera
StageState::~StageState(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

// Method responsible for preloading game state assets
void StageState::LoadAssets(){



}

// Update the state of entities, collision tests, and game termination check
void StageState::Update(float dt){
    InputManager& input = InputManager::GetInstance();
       
    Camera::Update(dt);

    // If the event is quit, set the termination flag
    if ((input.KeyPress(ESCAPE_KEY)) || input.QuitRequested()){
        quitRequested = true;
    }


    //============================ Checks for collisions ==================================== 
    std::vector<std::shared_ptr<GameObject>> obj_cl;

    for (const auto& obj : objectArray){
        auto clComponent = obj->GetComponent("Collider");
        
        if (clComponent){
            obj_cl.push_back(obj);
        }
    }

    for (size_t i = 0; i < obj_cl.size(); ++i){
        for (size_t j = i + 1; j < obj_cl.size(); ++j){
            if (Collision::IsColliding(obj_cl[i]->box, obj_cl[j]->box, obj_cl[i]->GetAngleRad(), obj_cl[j]->GetAngleRad())){
                obj_cl[i]->NotifyCollision(*obj_cl[j]);
                obj_cl[j]->NotifyCollision(*obj_cl[i]);
            }
        }
    }

    //============================ Checks whether to delete objects and updates ========================================
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




// Rendering the game state, including entities, backgrounds, HUD, and more.
void StageState::Render(){
    for (int i = 0; i != (int)objectArray.size(); i++){
        objectArray[i]->Render();
    }
}


void StageState::Start(){
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    } 
    music.Play(BG_MUSIC_LOOP);
    started = true;
}

void StageState::Pause(){
    music.Stop(0);
}

void StageState::Resume(){
    music.Play();
}    