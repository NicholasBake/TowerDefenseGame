#include <raylib.h>

enum TILE_TYPE{
    TOWER,
    PATH,
    BACKGROUND    
};

class Tile
{
private:
    void Scale();
public:

    TILE_TYPE TYPE;
    Texture2D texture;
    Tile(Texture2D Texture = LoadTexture(""), TILE_TYPE type = BACKGROUND);
};

