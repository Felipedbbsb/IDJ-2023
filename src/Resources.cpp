#include "Resources.h"

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

SDL_Texture *Resources::GetImage(std::string file){   
    SDL_Texture* texture;
    std::unordered_map<std::string, SDL_Texture*>::iterator it = Resources::imageTable.find(file);
    
    if (it != Resources::imageTable.end()){   
        return it->second;
        
    }

    std::cout << "Loading a new _image_ file... " << "(" << file << ")" << std::endl;
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    
    if(texture != nullptr){
       Resources::imageTable.insert({file, texture});
       std::cout << "---Loading done!--- " << "(" << file << ")" << std::endl;
       return texture;
    }
    
}

void Resources::ClearImages(){   
    int i = 0;
    while (imageTable.begin() != imageTable.end()){
        std::cout << "Cleaning image memories ->" << " (" << i + 1 << ") " << std::endl;
        imageTable.erase(imageTable.begin()++);
        i++;
    }
    std::cout << "---All images erased---" << std::endl;
}

Mix_Music *Resources::GetMusic(std::string file){
    Mix_Music *music;
    std::unordered_map<std::string, Mix_Music *>::iterator i = Resources::musicTable.find(file);
    if (i == Resources::musicTable.end()){
        std::cout << "Loading a new _music_ file... " << "(" << file << ")" << std::endl;
 
        music = Mix_LoadMUS(file.c_str());
        Resources::musicTable.insert({file, music});
        std::cout << "---Loading done!--- " << "(" << file << ")" << std::endl;
        return music;
    }
    return i->second;
}
    
void Resources::ClearMusics(){
    int i = 0;
    while (musicTable.begin() != musicTable.end()){
        std::cout << "Cleaning musics memories ->" << " (" << i + 1 << ") " << std::endl;
        musicTable.erase(musicTable.begin()++);
        i++;
    }
    std::cout << "---All musics erased---" << std::endl;
}

Mix_Chunk *Resources::GetSound(std::string file){
    Mix_Chunk *chunk;
    std::unordered_map<std::string, Mix_Chunk *>::iterator i = Resources::soundTable.find(file);
    if (i == Resources::soundTable.end()){
        std::cout << "Loading a new _sound_ file... " << "(" << file << ")" << std::endl;
        chunk = Mix_LoadWAV(file.c_str());
        Resources::soundTable.insert({file, chunk});
        std::cout << "Loading done! " << "(" << file << ")" << std::endl;
        return chunk;
    }
    return i->second;
}

void Resources::ClearSounds(){
    int i = 0;
    while (soundTable.begin() != soundTable.end()){
        std::cout << "Cleaning song memories ->" << " (" << i + 1 << ") " << std::endl;
        soundTable.erase(soundTable.begin()++);
        i++;
    }
    std::cout << "---All songs erased---" << std::endl;
}