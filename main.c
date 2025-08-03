#include<raylib.h>

typedef struct
{
    int width, height, speed;
    float posX, posY, velocity, gravity;
    bool isJumping;
} player;

int main()
{
    int windowWidth = GetMonitorWidth(0);
    int windowHeight = GetMonitorHeight(0);

    InitWindow(windowWidth, windowHeight, "=== REDRIOT ===");
    SetTargetFPS(60);
    ToggleFullscreen();

    windowWidth = GetScreenWidth();
    windowHeight = GetScreenHeight();

    player p1, p2;

    p1.width = 50; p1.height = 50; p1.speed = 5;
    p1.gravity = 0.5; p1.velocity = 0;
    p1.isJumping = false;
    p1.posX = (windowWidth/3)-(p1.width/2);
    p1.posY = (windowHeight/2)-(p1.height/2);

    p2.width = 50; p2.height = 50; p2.speed = 5;
    p2.gravity = 0.5; p2.velocity = 0;
    p2.isJumping = false;
    p2.posX = (2*windowWidth/3)-(p2.width/2);
    p2.posY = (windowHeight/2)-(p2.height/2);

    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_F11)) ToggleFullscreen();    
        if(IsKeyPressed(KEY_ESCAPE)) CloseWindow();
        

        if(IsKeyDown(KEY_RIGHT)) p1.posX += p1.speed;
        if(IsKeyDown(KEY_LEFT)) p1.posX -= p1.speed;
        
        if(IsKeyPressed(KEY_UP) && !p1.isJumping)
        {
            p1.velocity = -12;
            p1.isJumping = true;
        }
        p1.velocity += p1.gravity;
        p1.posY += p1.velocity;

        if(p1.posY + p1.height > windowHeight)
        {
            p1.posY = windowHeight - p1.height;
            p1.velocity = 0;
            p1.isJumping = false;
        }

        if(IsKeyDown(KEY_D)) p2.posX += p2.speed;
        if(IsKeyDown(KEY_A)) p2.posX -= p2.speed;
        
        if(IsKeyPressed(KEY_W) && !p2.isJumping)
        {
            p2.velocity = -12;
            p2.isJumping = true;
        }
        p2.velocity += p2.gravity;
        p2.posY += p2.velocity;

        if(p2.posY + p2.height > windowHeight)
        {
            p2.posY = windowHeight - p2.height;
            p2.velocity = 0;
            p2.isJumping = false;
        }


        if (CheckCollisionRecs(
            (Rectangle){p1.posX, p1.posY, p1.width, p1.height},
            (Rectangle){p2.posX, p2.posY, p2.width, p2.height}))
        {
            float overlap = 0;
            
            if (p1.posX < p2.posX) overlap = (p1.posX + p1.width) - p2.posX;
            else overlap = (p2.posX + p2.width) - p1.posX;

            if (overlap > 0)
            {
                float pushDistance = overlap*0.5;
                
                if (p1.posX < p2.posX)
                {
                    p1.posX -= pushDistance;
                    p2.posX += pushDistance;
                }
                else
                {
                    p1.posX += pushDistance;
                    p2.posX -= pushDistance;
                }
            }
        }

        if (p1.posX < 0) p1.posX = 0;
        if (p2.posX < 0) p2.posX = 0;
        if (p1.posX + p1.width > windowWidth) p1.posX = windowWidth - p1.width;
        if (p2.posX + p2.width > windowWidth) p2.posX = windowWidth - p2.width;

        
        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawRectangle(p1.posX, p1.posY, p1.width, p1.height, RED);
            DrawRectangle(p2.posX, p2.posY, p2.width, p2.height, BLUE);
        }
        EndDrawing();
    }

    return 0;
}
