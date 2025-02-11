#include <iostream>
//#include <chrono>
//#include <thread>
#include <raylib.h>
#include <array>
#include <vector>
#include "Tile.h"
/* 90X90 IS THE LARGEST MAP SIZE AS OF NOW I HAVE NO IDEA WHY BUT THE TILE MAP SYSTEM DOESN'T LIKE PROCESSING IMAGES ABOVE 90X90 RESOLUTION */
enum GAMESTATE{
    PLAYING,
    PAUSED,
    GAMEOVER,
    MAINMENU,
    MAP
};
GAMESTATE gameState = PLAYING;

Camera2D mainCamera = { 0 };

Texture2D LAZapTower = { 0 };
Texture2D LTZapTower = { 0 };
Texture2D RAZapTower = { 0 };
Texture2D RTZapTower = { 0 };
Texture2D GreenGrassBG = { 0 };
Texture2D PathBG = { 0 };

Image MAPIMAGE = { 0 };

// PUT ALL TEXTURES INTO THIS VECTOR - LOOP AT THE END OF THE MAIN GAME LOOP DELOADS ALL OF THESE FROM VRAM.
std::vector<Texture2D> textures;

//MAXIMUM # OF ROWS AND COLUMNS IN THE TILE MAP.
const size_t rows = 200;
const size_t columns = 200;

// Map contains the background tiles, the towers will be in a seperate vector as they don't have to be locked by grid
std::array<std::array<Tile, rows>, columns> Map;

std::vector<Tile> Towers;

float towerScale = 0.1f;

// UNPLACED TOWERS TILES
Tile zapTowerUnPlaced = Tile();

void Start(){
    // - INITIALISING TEXTURES - 
    LAZapTower = LoadTexture("../TowerDefenseGame/img/LAZapTower.png");
    textures.push_back(LAZapTower);
    
    LTZapTower = LoadTexture("../TowerDefenseGame/img/LTZapTower.png");
    textures.push_back(LAZapTower);
    
    RAZapTower = LoadTexture("../TowerDefenseGame/img/RAZapTower.png");
    textures.push_back(LAZapTower);
    
    RTZapTower = LoadTexture("../TowerDefenseGame/img/RTZapTower.png");
    textures.push_back(LAZapTower);

    GreenGrassBG = LoadTexture("../TowerDefenseGame/img/GrassGreenRender.png");
    textures.push_back(GreenGrassBG);

    PathBG = LoadTexture("../TowerDefenseGame/img/GroundPath.png");
    textures.push_back(PathBG);

    MAPIMAGE = LoadImage("../TowerDefenseGame/img/map.png");

    std::cout << MAPIMAGE.height << std::endl;
    // initialize the background vector
    for (int i = 0; i < MAPIMAGE.height; i++)
    {
        for (int j = 0; j < MAPIMAGE.width; j++)
        {
            Color pixelAtXY = GetImageColor(MAPIMAGE, j, i);
            // Take the pixels at coordinates XY and make tiles based on the colors of those pixels. 0x9c5a3c is a PATH tile, 0x22b14c is a GRASS tile
            if(ColorIsEqual(pixelAtXY, Color { 34, 177, 76, 255})){
                std::cout << "GRASSBG" << std::endl;
                Tile backgroundTile = Tile(GreenGrassBG, BACKGROUND);
                backgroundTile.texture.height = 150;
                backgroundTile.texture.width = 150;
                Map.at(i).at(j) = backgroundTile;
            }
            if(ColorIsEqual(pixelAtXY, Color { 156, 90, 60, 255 })){
                std::cout << "PATHBG" << std::endl;
                Tile backgroundTile = Tile(PathBG, BACKGROUND);
                backgroundTile.texture.height = 150;
                backgroundTile.texture.width = 150;
                Map.at(i).at(j) = backgroundTile; 
                //break;
            }
            
        }
    }
    
    UnloadImage(MAPIMAGE);

    zapTowerUnPlaced = Tile(RTZapTower, TOWER, 50, 50, towerScale);
    //Towers.push_back(zapTowerUnPlaced);
}
int mouseX = 0;
int mouseY = 0;
float mouseScrollSpeed = 0.050f;
void GameLogic(){
    if(IsKeyDown(KEY_G)){
        gameState = PAUSED;
    }
    mouseX = GetMousePosition().x;
    mouseY = GetMousePosition().y;
    if(IsKeyDown(KEY_W)){
        mainCamera.target.y -= 10;
    }
    if(IsKeyDown(KEY_A)){
        mainCamera.target.x -= 10;
    }
    if(IsKeyDown(KEY_S)){
        mainCamera.target.y += 10;
    }
    if(IsKeyDown(KEY_D)){
        mainCamera.target.x += 10;
    }
    
    // zoom functionality
    mainCamera.zoom += (GetMouseWheelMove() * mouseScrollSpeed);
    
    zapTowerUnPlaced.x = GetScreenToWorld2D(GetMousePosition(), mainCamera).x - (zapTowerUnPlaced.texture.width/2);
    zapTowerUnPlaced.y = GetScreenToWorld2D(GetMousePosition(), mainCamera).y- (zapTowerUnPlaced.texture.height/2);
}
void Paused(){
    BeginDrawing();
        BeginMode2D(mainCamera);
            DrawText("PAUSED", mainCamera.target.x + (500 - (MeasureText("PAUSED", 25)/2)), mainCamera.target.y + 500, 250, RED);
            if(IsKeyDown(KEY_H)){
                gameState = PLAYING;
                EndDrawing();
                return;
            }
        EndMode2D();
    EndDrawing();
}
void GameOver(){
    
}
void MapCreation(){

}
void MainMenu(){

}
// Method where we, well render. Using game logic updated every timestep, it renders each tile deciding its' color based on if the tile is a snake, food, or normal tile.
void Render(){
    
    //mainCamera.zoom = 1;
    
    BeginDrawing();
    if(gameState != PLAYING){
        EndDrawing();
        return;
    }
        BeginMode2D(mainCamera);
            // ---- DRAWING MAP ----
            int x = Map.at(0).at(0).texture.width;
            int y = 0;
            for (int i = 0; i < rows; i++)
            {
                
                for (int j = 0; j < columns; j++)
                {
                    
                    DrawTexture(Map.at(i).at(j).texture, x, y, WHITE);
                    
                    x += Map.at(0).at(0).texture.width;
                    
                }
                if(i % 2 != 0){
                    x = 0;
                    ////std::cout<< "MOVED OVER" << std::endl;
                }
                else{
                    x = Map.at(0).at(0).texture.width/2;
                    //std::cout<< "MOVED TO ZERO" << std::endl;
                }
                y += Map.at(0).at(0).texture.height/4.5f;
                
            }
            // ---- DRAWING TOWERS ----
            
            // Circle that indicated radious around tower where tower does damage.
            Color circleColor = Color { 0 };
            circleColor.a = 127;
            circleColor.r = 255;
            circleColor.b = 0;
            circleColor.g = 0;
            DrawCircle(GetScreenToWorld2D(GetMousePosition(), mainCamera).x, GetScreenToWorld2D(GetMousePosition(), mainCamera).y, 250, circleColor);

            DrawTexture(zapTowerUnPlaced.texture, zapTowerUnPlaced.x, zapTowerUnPlaced.y, WHITE);
            for (int i = 0; i < Towers.size(); i++)
            {
                DrawTexture(Towers.at(i).texture, Towers.at(i).x, Towers.at(i).y, WHITE);
            }
            
            ClearBackground(DARKPURPLE);
            EndMode2D();
    EndDrawing();
}

int main() 
{      
    InitWindow(1500, 1000, "Thermus Application");

    SetTargetFPS(60);
    
    mainCamera.zoom = 1;

    Start();
    while (!WindowShouldClose())
    {
        if(gameState == PLAYING){
            GameLogic();
            Render();
        }
        if(gameState == PAUSED){
            Paused();
        }
        if(gameState == GAMEOVER){
            GameOver();
        }
        if(gameState == MAP){
            MapCreation();
        }
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
