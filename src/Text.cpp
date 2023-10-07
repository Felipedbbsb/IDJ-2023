#include "Text.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int blinkPeriod)
    : Component::Component(associated),
      font(nullptr),
      texture(nullptr),
      text(text),
      style(style),
      fontFile(fontFile),
      fontSize(fontSize),
      color(color),
      blinkPeriod(blinkPeriod) {
      font = TTF_OpenFont(fontFile.c_str(), fontSize);
      RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) {
    if (blinkTimer.Get() < blinkPeriod) {
        blinkTimer.Update(dt);
    } 
    else {
        blinkTimer.Restart();
    }
}

void Text::Render() {
    if (blinkTimer.Get() <= blinkPeriod / 2) {
        SDL_Rect clipRect = {0, 0, static_cast<int>(associated.box.w), static_cast<int>(associated.box.h)};
        SDL_Rect dst = {static_cast<int>(associated.box.x + Camera::pos.x),
                        static_cast<int>(associated.box.y + Camera::pos.y),
                        clipRect.w,
                        clipRect.h};

        int RENDER_FAIL;
        RENDER_FAIL = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst, associated.angleDeg, nullptr, SDL_FLIP_NONE);
        if (RENDER_FAIL != 0) {
            std::cout << "Text: fail to render " << SDL_GetError() << std::endl;
        }
    }
}

void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    if (font == nullptr) {
        font = Resources::GetFont(fontFile, fontSize);
    }

    SDL_Surface* H_surface = nullptr;

    switch (style) {
        case SOLID: {
            H_surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        }
        case SHADED: {
            H_surface = TTF_RenderText_Shaded(font, text.c_str(), color, BACKGROUND_COLOR);
            break;
        }
        case BLENDED: {
            H_surface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
        }
    }

    int H_Width, H_Height;
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), H_surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &H_Width, &H_Height);

    associated.box.w = H_Width;
    associated.box.h = H_Height;

    SDL_FreeSurface(H_surface);
}

bool Text::Is(std::string type) {
    return (type == "Text");
}