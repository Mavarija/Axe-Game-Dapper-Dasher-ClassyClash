// Dapper Dasher.

#include "raylib.h"


struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    //update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        //update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // Window dimensions array:
    int windowDimensions[2];
    windowDimensions[0] = 512; // width
    windowDimensions[1] = 380; // height
    // Window variables:
    const char* winTitle{"Vaiva's Dasher!"};
    Color winColour{WHITE};

    // Initialize the window:
    InitWindow(windowDimensions[0], windowDimensions[1], winTitle);

    // Acceleration due to gravity (pixels/s)/s
    const int gravity{1000};


    // Hazard (Nebulae) variables:
    Texture2D nebula = LoadTexture("C:/textures/12_nebula_spritesheet.png");
    // Variable for number of hazards in our game, to use in loops:
    const int sizeOfNebulae{3};
    // Array of hazards (nebulae):
    AnimData nebulae[sizeOfNebulae]{};
    // For Loop of nebulae common variables:
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 2.2;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }
    // Nebula x velocity (pixels/second):
    int nebVel{-200};

    // Finish Line (after the last nebula in an array):
    float finishLine{nebulae[sizeOfNebulae - 1].pos.x};

    // Scarfy variables (long way to initialize):
    Texture2D scarfy = LoadTexture("C:/textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2; //center of windown
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height; //bottom of window
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;
    // Velocity var:
    int velocity{0};
    // Is player in air?
    bool isInAir{};
    // Jump velocity (pixels/second):
    const int jumpVel{-600};


    // Background vars:
    Texture2D background = LoadTexture("C:/textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("C:/textures/back-buildings.png");
    float mgX{};
    Texture2D foreground = LoadTexture("C:/textures/foreground.png");
    float fgX{};

    // Collision var:
    bool collision{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time (time since last frame):
        const float dT{GetFrameTime()};

        // Start drawing:
        BeginDrawing();
        ClearBackground(winColour);

        // Update background positions (scroll):
        bgX -= 20 * dT;
        if (bgX <= -background.width*2)
        {
            bgX = 0.0;  //background
        }
        mgX -= 40 * dT;
        if (mgX <= -midground.width*2)
        {
            mgX = 0.0;  //midground
        }
        fgX -= 80 * dT;
        if (fgX <= -foreground.width*2)
        {
            fgX = 0.0;  //foreground
        }
        // Draw backgrounds:
        Vector2 bg1Pos{bgX, 0.0};
        Vector2 bg2Pos{bgX + background.width*2, 0.0};  //background
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
        Vector2 mg1Pos{mgX, 0.0};
        Vector2 mg2Pos{mgX + midground.width*2, 0.0};   //midground
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);
        Vector2 fg1Pos{fgX, 0.0};
        Vector2 fg2Pos{fgX + foreground.width*2, 0.0};  //foreground
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        // Perform ground check:
        if (isOnGround(scarfyData, windowDimensions[1]))
        {
            // player is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // player is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // Jump check:
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // Update nebulae positions:
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }

        // Update finish line:
        finishLine += nebVel * dT;

        // Update scarfy Y position every frame:
        scarfyData.pos.y += velocity * dT;

        // Scarfy animation frame updates:
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }
        // Nebulae animation frame updates (forLoop):
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        // Collision range:
        for (AnimData nebula : nebulae)
        {
            float pad{50};  // pad - shrinks the collision size of the sprites, as they're too big.
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        // Collision check:
        if (collision)
        {
            // lose the game
            DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2, 40, RED);
        }
        else if (scarfyData.pos.x >= finishLine)
        {
            // win the game
            DrawText("You Win!", windowDimensions[0]/4, windowDimensions[1]/2, 40, RED);
        }
        else
        {
            // Draw nebulae:
            for (int i = 0; i < sizeOfNebulae; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            // Draw scarfy:
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        // Stop drawing:
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();

}