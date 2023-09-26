#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"

#define SETCLIP_X 0
#define SETCLIP_Y 0

Sprite::Sprite(GameObject &associated) : Component::Component(associated),
scale(Vec2(1, 1))
{
    texture = nullptr;
}



Sprite::Sprite(GameObject &associated, std::string file, 
int frameCount, 
float frameTime) : Sprite(associated)
{
    this->frameTime = frameTime;
    this->frameCount = frameCount;
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
    associated.box.w = w * scale.x;
    associated.box.h = h * scale.y;
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
    SDL_Rect dstLoc = {int(associated.box.x) + (int)Camera::pos.x, int(associated.box.y) + (int)Camera::pos.y, (int)(clipRect.w * GetScale().x), (int)(clipRect.h * GetScale().y)};

    //RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (RENDER_ERROR != 0) {
        std::cout << "Texture render failure " << SDL_GetError() << std::endl;
    }
}

void Sprite::Render(int x, int y){
    int RENDER_ERROR;
    SDL_Rect dstLoc = {(int)(x * GetScale().x) + (int)Camera::pos.x, (int)(y * GetScale().y) + (int)Camera::pos.y, (int)(clipRect.w * GetScale().x), (int)(clipRect.h * GetScale().y)};
    
    //RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (RENDER_ERROR != 0){
        std::cout << "Texture render failure " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetWidth(){   
    return (width * scale.x) / frameCount;
}

//int Sprite::GetWidth() {return width;}

int Sprite::GetHeight() {
    return height * scale.y;
}

//int Sprite::GetHeight() {return height;}

Vec2 Sprite::GetScale(){return scale;}

void Sprite::SetScale(float scaleX, float scaleY){
    if (scaleX != 0){
       scale.x = scaleX;
       associated.box.w = clipRect.w * scale.x;
    }
    if (scaleY != 0){
       scale.y = scaleY;
       associated.box.h = clipRect.h * scale.y;

    }
}




//Retorna true se texture estiver alocada.
bool Sprite::IsOpen() {
    if (texture == nullptr) {
        return false;
    } else {
        return true;
    }
}

void Sprite::Update(float dt) {
    timeElapsed += dt; // Verifica em que momento de frame o sprite está
    if (timeElapsed >= frameTime) { // Passa para o próximo frame
        currentFrame = (currentFrame + 1) % frameCount; // Evita que currentFrame ultrapasse frameCount
        
        SetFrame(currentFrame);
        timeElapsed = 0;
    }
}


void Sprite::SetFrame(int frame){   
    timeElapsed = 0;
    currentFrame = frame;
    SetClip(currentFrame * (GetWidth() / scale.x), SETCLIP_Y, GetWidth() / scale.x, GetHeight() / scale.y );
}
void Sprite::SetFrameCount(int frameCount){
    this->frameCount = frameCount;
    SetFrame(0);
    associated.box.w = GetWidth();
    associated.box.DefineCenter(associated.box.x, associated.box.y);
}

void Sprite::SetFrameTime(float frameTime){   
    this->frameTime = frameTime;
}

bool Sprite::Is(std::string type){
    if (type == "Sprite"){return true;}
    else{return false;}
}