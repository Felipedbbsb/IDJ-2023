#include "Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component::Component(associated),
distanceLeft(maxDistance),
damage(damage){
    // Crie o Sprite diretamente com smart pointer
    auto bullet_spr = std::make_shared<Sprite>(associated, sprite);
    bullet_spr->SetScale(1.5, 1.5);
    associated.AddComponent(bullet_spr);

    // Calcule a velocidade diretamente no construto
    this->speed = Vec2(cos(angle) * speed, sin(angle) * speed);
    associated.angleDeg = this->speed.RotateDegree();
}

void Bullet::Update(float dt) {
    Vec2 movementBullet(speed.x * dt, speed.y * dt);
    associated.box.DefineCenter(associated.box.GetCenter() + movementBullet);

    distanceLeft -= movementBullet.Hypotenuse();

    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
    return (type == "Bullet");
}

int Bullet::GetDamage() {
    return damage;
}