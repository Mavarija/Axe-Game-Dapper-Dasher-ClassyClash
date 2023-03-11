// Axe Game

#include "raylib.h"

int main()
{
//Window dimensions:
    int width{800};
    int height{450};
    const char* window{"Vaiva's Window!"};

    InitWindow(width,height,window);

//Circle coordinates (window left-ish center,r-25,blue) for DrawCircle():
    int circleX{200};
    int circleY{200};
    float circleR{25};
    Color circleC{BLUE};
//Circle edges:
    int lCircleX{circleX - circleR};
    int rCircleX{circleX + circleR};
    int uCircleY{circleY - circleR};
    int bCircleY{circleY + circleR}; 

//Rectangle (axe) coordinates (window top center, h/w-50,red) for DrawRectangle():
    int rectX{400};
    int rectY{0};
    int rectW{50};
    int rectH{50};
    Color rectC{RED};
//Rectangle edges:
    int lRectX{rectX};
    int rRectX{rectX + rectW};
    int uRectY{rectY};
    int bRectY{rectY + rectH};

//DrawText parameters:
    const char* text{"Game Over!"};
    int textX{400};
    int textY{200};
    int textFontS{20};
    Color textC{RED};

//Collision with rectangle:
    bool collisionWithRect = 
                        (bRectY >= uCircleY) && 
                        (uRectY <= bCircleY) && 
                        (lRectX <= rCircleX) && 
                        (rRectX >= lCircleX);


//Shape move direction:
    int direction{10};

//Set frames per second:
    SetTargetFPS(60);

//Set up and tear down for a while loop:
    while(WindowShouldClose() == false)
    {    
        BeginDrawing();
        ClearBackground(WHITE);

        if (collisionWithRect)
        {
            DrawText(text,textX,textY,textFontS,textC);
        }
        else
        {
    //Game logic begins:

            //updates the edges as they move:
            lCircleX = circleX - circleR;
            rCircleX = circleX + circleR;
            uCircleY = circleY - circleR;
            bCircleY = circleY + circleR; 
            lRectX = rectX;
            rRectX = rectX + rectW;
            uRectY = rectY;
            bRectY = rectY + rectH;
    
            //updates the collision with rect, each frame:
            collisionWithRect = 
                        (bRectY >= uCircleY) && 
                        (uRectY <= bCircleY) && 
                        (lRectX <= rCircleX) && 
                        (rRectX >= lCircleX);

            //draws and moves circle side to side, using A and D keys:
            DrawCircle(circleX,circleY,circleR,circleC);

            if (IsKeyDown(KEY_D) && circleX < width)
            {
                circleX+=10;
            }    
            if (IsKeyDown(KEY_A) && circleX > 0)
            {
                circleX-=10;
            }
            //draws and moves rect up and down, automatically:
            DrawRectangle(rectX,rectY,rectW,rectH,rectC);

            rectY += direction;

            if(rectY > height || rectY < 0)
            {
                direction = -direction;
            }
        }

    //Game logic ends:
                
        EndDrawing();
    }

}