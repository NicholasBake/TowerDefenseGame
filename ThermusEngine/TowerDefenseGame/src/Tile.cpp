#include "Tile.h"

void Tile::SetScale(float i){
    //Scale = i;
    texture.height *= i;
    texture.width *= i;
}
