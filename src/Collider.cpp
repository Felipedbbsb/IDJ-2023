#include "Collider.h"


#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>


Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component::Component(associated),
                                                                      scale(scale),
                                                                      offset(offset)
{}

void Collider::Update(float dt){
    this->box = associated.box;
    this->box.w = this->box.w * scale.x;
    this->box.h = this->box.h * scale.y;

    float rotationInDegrees = offset.RotateDegree();
    Vec2 rotationVector(rotationInDegrees, 0); // Criar um vetor com a rotação em graus
    Vec2 resultVector = rotationVector + offset; // Somar o vetor de rotação com offset
    this->box.DefineCenter(associated.box.GetCenter() + resultVector);


}

void Collider::Render(){

}

bool Collider::Is(std::string type){
    return (type == "Collider");
}

void Collider::SetScale(Vec2 scale){
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
    this->offset = offset;
}

void Collider::NotifyCollision(GameObject &other)
{}