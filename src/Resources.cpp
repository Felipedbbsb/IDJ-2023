#include "Resources.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    SDL_Texture* texture = nullptr;
    
    try {
        auto it = Resources::imageTable.find(file);
        
        if (it != Resources::imageTable.end()) {
            return it->second;
        }

        std::cout << "Loading a new image file... (" << file << ")" << std::endl;
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

        if (texture != nullptr) {
            Resources::imageTable.insert({file, texture});
            std::cout << "Loading done! (" << file << ")" << std::endl;
            return texture;
        } else {
            throw std::runtime_error("Failed to load image file: " + file);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // Tratamento de erro: Encerrar o jogo ou realizar ações apropriadas em caso de falha na inicialização.
        // Neste exemplo, apenas registramos o erro no console.
        return nullptr;
    }
}

void Resources::ClearImages() {
    int i = 0;
    for (auto it = imageTable.begin(); it != imageTable.end(); ++it) {
        std::cout << "Cleaning image memory -> (" << i + 1 << ") File: " << it->first << std::endl;
        SDL_DestroyTexture(it->second);
        i++;
    }
    imageTable.clear();
    std::cout << "---All images erased---" << std::endl;
}


Mix_Music* Resources::GetMusic(std::string file) {
    Mix_Music* music = nullptr;

    try {
        auto it = Resources::musicTable.find(file);
        if (it == Resources::musicTable.end()) {
            std::cout << "Loading a new music file... (" << file << ")" << std::endl;
            music = Mix_LoadMUS(file.c_str());

            if (music != nullptr) {
                Resources::musicTable.insert({file, music});
                std::cout << "Loading done! (" << file << ")" << std::endl;
                return music;
            } else {
                throw std::runtime_error("Failed to load music file: " + file);
            }
        }
        return it->second;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // Tratamento de erro: Encerrar o jogo ou realizar ações apropriadas em caso de falha na inicialização.
        // Neste exemplo, apenas registramos o erro no console.
        return nullptr;
    }
}

void Resources::ClearMusics() {
    int i = 0;
    for (auto it = musicTable.begin(); it != musicTable.end(); ++it) {
        std::cout << "Cleaning music memory -> (" << i + 1 << ") File: " << it->first << std::endl;
        Mix_FreeMusic(it->second);
        i++;
    }
    musicTable.clear();
    std::cout << "---All musics erased---" << std::endl;
}

Mix_Chunk* Resources::GetSound(std::string file) {
    Mix_Chunk* chunk = nullptr;

    try {
        auto it = Resources::soundTable.find(file);
        if (it == Resources::soundTable.end()) {
            std::cout << "Loading a new sound file... (" << file << ")" << std::endl;
            chunk = Mix_LoadWAV(file.c_str());

            if (chunk != nullptr) {
                Resources::soundTable.insert({file, chunk});
                std::cout << "Loading done! (" << file << ")" << std::endl;
                return chunk;
            } else {
                throw std::runtime_error("Failed to load sound file: " + file);
            }
        }
        return it->second;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // Tratamento de erro: Encerrar o jogo ou realizar ações apropriadas em caso de falha na inicialização.
        // Neste exemplo, apenas registramos o erro no console.
        return nullptr;
    }
}

void Resources::ClearSounds() {
    int i = 0;
    for (auto it = soundTable.begin(); it != soundTable.end(); ++it) {
        std::cout << "Cleaning sound memory -> (" << i + 1 << ") File: " << it->first << std::endl;
        Mix_FreeChunk(it->second);
        i++;
    }
    soundTable.clear();
    std::cout << "---All sounds erased---" << std::endl;
}