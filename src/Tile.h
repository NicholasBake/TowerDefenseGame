#include "include.h"

enum TILE_TYPE{
    TOWER,
    PATH,
    BACKGROUND    
};

class Tile
{
private:

public:

    TILE_TYPE TYPE;
    Texture2D texture;
    float x;
    float y;
    void SetScale(float i);
    Tile() {};
    Tile(Texture2D Texture, float scale) : texture(Texture){SetScale(scale);}
    Tile(Texture2D Texture, TILE_TYPE type) : texture(Texture), TYPE(type){};
    Tile(Texture2D Texture, TILE_TYPE type, float x, float y, float scale) : texture(Texture), TYPE(type), x(x), y(y){};
    
    
};

