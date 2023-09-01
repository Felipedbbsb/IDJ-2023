#include "../include/Sprite.h"
#include "../include/Game.h"

#define CLIP_START_X 0
#define CLIP_START_Y 0

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(std::string file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    };
}

//Carrega a imagem indicada pelo caminho file.
void Sprite::Open(std::string file) {
    if (texture != nullptr) {
       SDL_DestroyTexture(texture);
    };
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr)
    {
        std::cout << "Failed to load texture" << std::endl;
    } else {
        std::cout << "Texture loaded successfully!" << std::endl;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
    SetClip(CLIP_START_X, CLIP_START_Y, width, height);
}

//Seta clipRect com os parâmetros dados.
void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}



//Render é um wrapper para SDL_RenderCopy, que recebe quatro argumentos.
// -SDL_Renderer* renderer: O renderizador de Game.
// -SDL_Texture* texture: A textura a ser renderizada;
// -SDL_Rect* srcrect: O retângulo de clipagem. Especifica uma área da textura a ser "recortada" e renderizada.
//- SDL_Rect* dstrect: O retângulo destino. Determina a posição na tela
//em que a textura deve ser renderizada (membros x e y). Se os membros
//w e h diferirem das dimensões do clip, causarão uma mudança na
//escala, contraindo ou expandindo a imagem para se adaptar a esses
//valores.

void Sprite::Render(int x, int y) {
    int RENDER_ERROR;
    SDL_Rect dstLoc = {x, y, GetWidth(), GetHeight()};

    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0) {
        std::cout << "Texture render failure " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

//Retorna true se texture estiver alocada.
bool Sprite::IsOpen() {
    std::cout << texture << std::endl;
    if (texture == nullptr) {
        return false;
    } else {
        return true;
    }
}