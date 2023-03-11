#include "enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    worldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;

    width = texture.width / maxFrame;
    height = texture.height;

    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive()) return;
    // Assign value to velocity:
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    // Check velocity length:
    if (Vector2Length(velocity) < radius) velocity = {};

    // Calling the parent class tick function to draw the enemy:
    BaseCharacter::tick(deltaTime);
    
    // If collision with target = takeDamage.
    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

// deriving the Screen position:
Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}