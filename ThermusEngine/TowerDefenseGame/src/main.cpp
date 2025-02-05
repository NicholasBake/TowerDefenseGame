#include <iostream>
//#include <chrono>
//#include <thread>
#include <raylib.h>
#include <array>
#include <vector>
#include "Tile.h"

Camera2D mainCamera = { 0 };

Texture2D LAZapTower = { 0 };

Tile zapTowerUnPlaced = Tile();
float X = 0;
float Y = 0;

void GameLogic(){
    
}
void Paused(){
    
}
void GameOver(){
    
}


// Method where we, well render. Using game logic updated every timestep, it renders each tile deciding its' color based on if the tile is a snake, food, or normal tile.
void Render(){
    mainCamera.zoom = 1;
    
    BeginDrawing();
        BeginMode2D(mainCamera);
            DrawTexture(LAZapTower, X - LAZapTower.width/2, Y - LAZapTower.height/2, WHITE);
            ClearBackground(DARKPURPLE);
            EndMode2D();
    EndDrawing();
}

std::vector<Texture2D> textures;
int main() 
{  
    zapTowerUnPlaced = Tile(TOWER);
    
    InitWindow(1000, 1000, "Thermus Application");
    // - INITIALISING TEXTURES - 
    LAZapTower = LoadTexture("/media/nicholas/E/Tower-defense/ThermusEngine/TowerDefenseGame/img/LAZapTower.png");
    textures.push_back(LAZapTower);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        GameLogic();
        Render();
    }
    
    for (int i = 0; i < textures.size(); i++)
    {
        UnloadTexture(textures.at(i));
    }
    
    UnloadTexture(LAZapTower);
    CloseWindow();
    return 0;
}
