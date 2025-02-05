enum TILE_TYPE{
    TOWER,
    PATH,
    BACKGROUND
};
class Tile
{
private:
    /* data */
public:
    
    TILE_TYPE TYPE;
    int scaleX;
    int scaleY;
    Tile(TILE_TYPE type = BACKGROUND, int XScale = 1, int YScale = 1);
};

