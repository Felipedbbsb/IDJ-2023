#include "Bullet.h"
#include "Collider.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, std::string WhoShooter) : Component::Component(associated),
distanceLeft(maxDistance),
damage(damage){
    // Crie o Sprite diretamente com smart pointer, determinando se é minion ou penguin
    auto bullet_spr = std::make_shared<Sprite>(associated, sprite);
    //bullet_spr->SetScale(1.5, 1.5);
    associated.AddComponent(bullet_spr);

    // Adicionando Collider
    Collider *bullet_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)bullet_collider);

    // Calcule a velocidade diretamente no construto
    this->speed = Vec2::FromAngle(angle) * speed;
    associated.angleDeg = this->speed.RotateDegree();
}
void Bullet::Update(float dt) {
    Vec2 movementBullet = speed * dt;
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

void Bullet::NotifyCollision(GameObject &other)
{   
    std::cout << other.GetComponent("Minion") << other.GetComponent("Alien") << other.GetComponent("PenguinBody") << std::endl;
    //Caso de colisao bullet com enemy
    if ((other.GetComponent("Minion") || other.GetComponent("Alien")) && WhoShooter =="Penguin") {
		associated.RequestDelete();
	}
    //Caso de colisao bullet com penguin
	if (other.GetComponent("PenguinBody") && WhoShooter =="Enemy") {
		associated.RequestDelete();
	}
}