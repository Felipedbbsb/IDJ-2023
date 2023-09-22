#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"

#define SETCLIP_X 0
#define SETCLIP_Y 0

Sprite::Sprite(GameObject &associated) : Component::Component(associated),
                                         scale(Vec2(1, 1)){
    texture = nullptr;

}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated){
    Open(file);
}

Sprite::~Sprite(){}

// Carrega a imagem indicada pelo caminho file.
void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file.c_str());

    if (texture == nullptr){
        std::cout << "Failed to load texture" << std::endl; // falha em carregar imagem.
    } 
    else {
        std::cout << "Texture loaded successfully!" << std::endl;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
    SetClip(SETCLIP_X, SETCLIP_Y, width, height);
}

//Seta clipRect com os parâmetros dados.
void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    //Hitbox do tamanho do sprite
    associated.box.w = w;
    associated.box.h = h;
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

void Sprite::Render() {
    int RENDER_ERROR;
    SDL_Rect dstLoc = {int(associated.box.x) + (int)Camera::pos.x, int(associated.box.y) + (int)Camera::pos.y, clipRect.w, clipRect.h};

    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0) {
        std::cout << "Texture render failure " << SDL_GetError() << std::endl;
    }
}

void Sprite::Render(int x, int y){
    int RENDER_ERROR;
    SDL_Rect dstLoc = {x + (int)Camera::pos.x, y + (int)Camera::pos.y, clipRect.w, clipRect.h};
    
    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    //RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (RENDER_ERROR != 0){
        std::cout << "Texture render failure " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetWidth() {return width;}

int Sprite::GetHeight() {return height;}

Vec2 Sprite::GetScale(){return scale;}

void Sprite::SetScale(float scaleX, float scaleY){
    if (scaleX != 0){
       scale.x = scaleX;
       associated.box.w = associated.box.w * scale.x;
    }
    if (scaleY != 0){
       scale.y = scaleY;
       associated.box.h = associated.box.h * scale.y;

    }
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


void Sprite::Update(float dt){}

bool Sprite::Is(std::string type){
    if (type == "Sprite"){return true;}
    else{return false;}
}