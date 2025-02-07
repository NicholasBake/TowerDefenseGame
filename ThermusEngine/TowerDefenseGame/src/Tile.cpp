#include "Tile.h"

void Tile::SetScale(float i){
    Scale = i;
    texture.height *= Scale;
    texture.width *= Scale;
}
Tile::Tile(Texture2D Texture, TILE_TYPE type, float x, float y, float scale){
    TYPE = type;
    texture = Texture;
    x = x;
    y = y;

    Scale = scale;
    texture.height *= Scale;
    texture.width *= Scale;
}