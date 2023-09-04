#include "Sound.h"
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
Sound::Sound(GameObject &associated) : Component::Component(associated){
    chunk = nullptr;
}

Sound::Sound(GameObject &associated, std::string file) : Sound(associated){
    Open(file.c_str());
}



void Sound::Play(int times){
    //channel = Mix_PlayChannel(-1, chunk, times - 1);
    channel = -1; 
    if (channel == -1)
    {
        std::cout << "Failed to play sound!" << SDL_GetError() << std::endl;
    }
}

void Sound::Stop(){
    chunk = nullptr;
    if (chunk != nullptr){
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file){
    //chunk = Mix_LoadWAV(file.c_str());
    chunk = nullptr;
    if (chunk == nullptr)
    {
        std::cout << "Failed to open sound!" << std::endl;
    } 
  
}

Sound::~Sound(){
    if (chunk != nullptr)
    {
        while (Mix_Playing(channel));
        Stop();
        Mix_FreeChunk(chunk);
    }
}

bool Sound::Is(std::string type){
    if (type == "Sound")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Sound::Update(float dt){

}

void Sound::Render(){

}


