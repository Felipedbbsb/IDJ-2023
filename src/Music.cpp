#include <iostream>
#include "Music.h"


Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    music = nullptr;
    Open(file);
}

//Se loops(times) for -1, a música repete infinitamente. Se loops for 0, a música não é tocada.
//Vale notar que a Mixer só suporta uma música sendo tocada por vez: 
//Se outra música já estiver tocando, ela para.
void Music::Play(int times){
    if (music != nullptr){
        Mix_PlayMusic(music, times);
    }
    else{
        std::cout << "SDL_MUSIC = nullptr";
    }
}

//default como 1,5 segundos. Caso queria que pare
//imediatamente, basta passar 0 como argumento.
void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){
    music = Mix_LoadMUS(file.c_str()); // const char* file
    if(music == nullptr){
        std::cout << "Error loading music!"<< std::endl;
    } 
    else {
        std::cout << "Music uploaded successfully!" << std::endl;
    }
}

//Checa se music é nula.
bool Music::IsOpen() {
    if (music != nullptr) {
        return true;
    } 
    else {
        return false;
    }
}

Music::~Music() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}