#include <raylib.h>

enum TILE_TYPE{
    TOWER,
    PATH,
    BACKGROUND    
};

class Tile
{
private:
    //void Scale();
    float Scale;
public:

    TILE_TYPE TYPE;
    Texture2D texture;
    float x;
    float y;
    void SetScale(float i);
    Tile(Texture2D Texture = LoadTexture(""), TILE_TYPE type = BACKGROUND, float x = 0, float y = 0, float scale = 1);
};

