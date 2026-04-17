#include "SDL_include.h"
#include "Sprite.h"
#include <string>

class TileSet{
    public:
        TileSet(int tileWidth, int tileHeight, std::string file);
        
        void RenderTile(unsigned index, float x, float y);

        int GetTileWidth();
        int GetTileHeight();

    private:
        Sprite tileSet;
        
        int tileWidth;
        int tileHeight;
        int tileCount;
};
