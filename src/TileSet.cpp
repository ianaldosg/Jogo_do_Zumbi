#include "../include/TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) 
    : tileWidth(tileWidth), tileHeight(tileHeight), tileSet(file){
        if (tileSet.IsOpen()) {
            int imageWidth = tileSet.GetWidth(); 
            int imageHeight = tileSet.GetHeight();

            int columns = imageWidth / tileWidth;
            int rows = imageHeight / tileHeight;

            tileCount = columns * rows;

            tileSet.SetFrameCount(columns, rows); 
        }
    }

void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index < (unsigned)tileCount) {
        tileSet.SetFrame(index);
        tileSet.Render(x, y, tileWidth, tileHeight);
    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}

