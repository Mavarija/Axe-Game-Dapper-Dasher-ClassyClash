#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "baseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() {return weaponCollisionRec;}
    float getHealth() const {return health;}
    void takeDamage(float damage);
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("D:/Programming/Projects/Udemy/Cpp Fundamentals - Game Prog for Beginners + Raylib/3. Classy Clash/files/characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif