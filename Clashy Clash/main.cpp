// Clashy Clash

#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

int main()
{
    // Window:
    const int winWidth{384};
    const int winHeight{384};
    InitWindow(winWidth, winHeight, "Vaiva's Top Down");

    // Map:
    Texture2D map = LoadTexture("C:/nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f}; //bcz the textures are tiny, we need to scale the map.

    // An instance of the Character class:
    Character knight{winWidth, winHeight};

    // An array holding props:
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("C:/nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("C:/nature_tileset/Log.png")},
    };

    // An instance of the Enemy class:
    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("C:/characters/goblin_idle_spritesheet.png"),
        LoadTexture("C:/characters/goblin_run_spritesheet.png")
    };
    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("C:/characters/slime_idle_spritesheet.png"),
        LoadTexture("C:/characters/slime_run_spritesheet.png")
    };

    // An array of Enemies:
    Enemy* enemies[]{
        &goblin,
        &slime
    };

    // Set target:
    for (auto enemy : enemies)
    {
        enemy ->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Gets character's worldPos vector each frame and flips it:
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map:
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // Draw the props:
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos()); 
        }

        // Check if the character is (not)alive:
        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        // Call the tick function for knight every frame:
        knight.tick(GetFrameTime());

        // Check map bounds:
        if(knight.getWorldPos().x < 0.f || 
           knight.getWorldPos().y < 0.f ||
           knight.getWorldPos().x + winWidth > map.width * mapScale ||
           knight.getWorldPos().y + winHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check collision with props:
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        // Calls enemy tick function by looping through the enemy array:
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }


        // Collision check for sword:
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            } 
        }

        EndDrawing();
    }
    CloseWindow();
}