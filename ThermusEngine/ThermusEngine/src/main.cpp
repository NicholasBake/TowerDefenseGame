#include <iostream>
//#include <chrono>
//#include <thread>
#include <raylib.h>
#include <array>
#include <vector>

void GameLogic(int lastKeyPressed){
        
}
void Paused(){
    
}
void GameOver(){
    
}
// Method where we, well render. Using game logic updated every timestep, it renders each tile deciding its' color based on if the tile is a snake, food, or normal tile.
void Render(){
        BeginDrawing();
            ClearBackground(DARKPURPLE);
        EndDrawing();
}

int main() 
{   
    InitWindow(800, 800, "Thermus Application");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Render();
    }
    
    CloseWindow();
    return 0;
}
