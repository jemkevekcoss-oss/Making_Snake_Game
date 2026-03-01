#include <iostream>
#include "ObjectClasses.h"


using namespace std;



int main() {
     
    //Creating the Window
    InitWindow(2*offset + CellSize*CellCount, 2 * offset + CellSize * CellCount, "SNAKE GAME");
    SetTargetFPS(60);

    double lastUpdateTime = 0;

    Game game = Game();
    // Input -> Update -> Draw
    while (!WindowShouldClose()) {

        // ---- 1. INPUT (Xử lý phím bấm) ----
          if (IsKeyPressed(KEY_UP) && game.snake.direction != Vector2{ 0, 1 }) {
            game.snake.direction = { 0,-1 }; game.running = true;
        } if (IsKeyPressed(KEY_DOWN) && game.snake.direction != Vector2{ 0, -1 }) {
            game.snake.direction = { 0, 1 }; game.running = true;
        } if (IsKeyPressed(KEY_LEFT) && game.snake.direction != Vector2{ 1, 0 }) {
            game.snake.direction = { -1, 0 }; game.running = true;
        } if (IsKeyPressed(KEY_RIGHT) && game.snake.direction != Vector2{ -1, 0 }) {
            game.snake.direction = { 1, 0 }; game.running = true;
        }   
        
        
        // ---- 2. UPDATE (Cập nhật logic) ----
        if (eventTrigger(0.2, lastUpdateTime)) {
            game.Update();
        }

        // ---- 3. DRAW (Vẽ lên màn hình) ----
        BeginDrawing();
        ClearBackground(WHITE); // Luôn gọi lệnh này đầu tiên sau BeginDrawing
        //DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color); -> Độ dày 1 pixel 
        //DrawLineEx(Vector2 startPos, Vector2 endPos, float thickness, Color color); 
        //DrawText(text,posX,posY,frontSize,color);
        
        DrawRectangleLinesEx(Rectangle{offset-5,offset-5,(float)CellSize * CellCount + 10,(float)CellSize * CellCount  + 10}, 5, darkgreen);
        game.Draw();


        //DrawText("TEXT",posX,posY,frontSize,Color);


        DrawText("SNAKE GAME", offset, offset-40, 35, darkgreen);
        
        string Score = "YOUR SCORE: " + to_string(game.score);
        DrawText(Score.c_str(), (float)CellSize * CellCount - 110, offset + CellSize * CellCount + 10, 25, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}



/*
"C:\SnakeGameWithRaylib\Images\Apple_snakeGame.jpg"
DrawRectangle(position.x*CellSize, position.y * CellSize, CellSize, CellSize, darkgreen);
*/