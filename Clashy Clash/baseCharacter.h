#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() {return alive;}
    void setAlive(bool isAlive) {alive = isAlive;}
protected:
    Texture2D texture{LoadTexture("C:/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("C:/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("C:/characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // Movement direction (texture):
    float rightLeft{1.f};

    // Animation:
    float runninTime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{4.0f};
    float  width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};
private:
    bool alive{true};
};

#endif