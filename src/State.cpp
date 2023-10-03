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
        //CameraFollower *penguin_cmfl = new CameraFollower(*penguinBody);
        penguinBody->AddComponent((std::shared_ptr<PenguinBody>)penguinBody_behaviour);
       // penguinBody->AddComponent((std::shared_ptr<CameraFollower>)penguin_cmfl);

        AddObject(penguinBody);

    // ===================== ALIEN 1 ===============================
    GameObject *alien = new GameObject();
        int randomMinions = 2 + (rand() % 4); // Minimum of 2 and maximum of 6 minions
        Alien *behaviour = new Alien(*alien, randomMinions);
        alien->AddComponent((std::shared_ptr<Alien>)behaviour);

        alien->box.x = 512;
        alien->box.y = 300;

        AddObject(alien);

    // ===================== ALIEN 2 ===============================
    //GameObject *alien2 = new GameObject();
    //    Alien *behaviour2 = new Alien(*alien2, randomMinions);
    //    alien2->AddComponent((std::shared_ptr<Alien>)behaviour2);

    //    alien2->box.x = 912;
    //    alien2->box.y = 800;

    //    AddObject(alien2);


    LoadAssets();
    music.Open(BG_MUSIC);
    music.Play(BACKGROUND_MUSIC_LOOP_TIMES);
}

State::~State(){objectArray.clear();}

// Method responsible for preloading game state assets
void State::LoadAssets(){
}

// Update the state of entities, collision tests, and game termination check
void State::Update(float dt){
    InputManager& input = InputManager::GetInstance();
       
    Camera::Update(dt);

    // If the event is quit, set the termination flag
    if ((input.KeyPress(ESCAPE_KEY)) || input.QuitRequested()){
        quitRequested = true;
    }


    // Verifica se há colisões  
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

    //Verifica se deve deletar objetos
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
