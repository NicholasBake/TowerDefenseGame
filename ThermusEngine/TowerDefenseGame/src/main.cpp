#include <iostream>
//#include <chrono>
//#include <thread>
#include <raylib.h>
#include <array>
#include <vector>
#include "Tile.h"

Camera2D mainCamera = { 0 };

Texture2D LAZapTower = { 0 };
Texture2D LTZapTower = { 0 };
Texture2D RAZapTower = { 0 };
Texture2D RTZapTower = { 0 };
Texture2D GreenGrassBG = { 0 };

// PUT ALL TEXTURES INTO THIS VECTOR - LOOP AT THE END OF THE MAIN GAME LOOP DELOADS ALL OF THESE FROM VRAM.
std::vector<Texture2D> textures;

const size_t rows = 50;
const size_t columns = 50;

// Map contains the background tiles, the towers will be in a seperate vector as they don't have to be locked by grid
std::array<std::array<Tile, columns>, rows> Map;

void Start(){
    // Need atleast one row of tiles in the map so out of range isn't thrown when initializing the map

    // - INITIALISING TEXTURES - 
    LAZapTower = LoadTexture("../img/LAZapTower.png");
    textures.push_back(LAZapTower);
    
    LTZapTower = LoadTexture("../TowerDefenseGame/img/LTZapTower.png");
    textures.push_back(LAZapTower);
    
    RAZapTower = LoadTexture("../TowerDefenseGame/img/RAZapTower.png");
    textures.push_back(LAZapTower);
    
    RTZapTower = LoadTexture("../TowerDefenseGame/img/RTZapTower.png");
    textures.push_back(LAZapTower);

    GreenGrassBG = LoadTexture("../TowerDefenseGame/img/GrassGreenRender.png");
    textures.push_back(GreenGrassBG);

    // initialize the background vector
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            Tile backgroundTile = Tile(GreenGrassBG, BACKGROUND);
            backgroundTile.texture.height = 150;
            backgroundTile.texture.width = 150;
            Map.at(i).at(j) = backgroundTile;   
        }
        
    }
    
}
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
            // ---- DRAWING MAP ----
            int x = 0;
            int y = 0;
            for (int i = 1; i < Map.size(); i++)
            {
                for (int j = 0; j < Map.at(i).size(); j++)
                {
                    DrawTexture(Map.at(i).at(j).texture, x, y, WHITE);
                    x += Map.at(i).at(j).texture.width;
                }
                if(i % 2 != 0){
                    x = Map.at(i).at(0).texture.width/2;
                }
                else{
                    x = 0;
                }
                y += Map.at(i).at(0).texture.height/4.1f;
            }
            
            ClearBackground(DARKPURPLE);
            EndMode2D();
    EndDrawing();
}

int main() 
{      
    InitWindow(1000, 1000, "Thermus Application");

    SetTargetFPS(60);

    Start();
    while (!WindowShouldClose())
    {
        GameLogic();
        Render();
    }
    
    // UNLOADING ALL TEXTURES
    for (int i = 0; i < textures.size(); i++)
    {
        UnloadTexture(textures.at(i));
    }
    
    UnloadTexture(LAZapTower);
    CloseWindow();
    return 0;
}
