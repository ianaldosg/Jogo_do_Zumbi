#include "../include/TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) 
    : tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight){
        if (!tileSet.IsOpen()) {
            std::cout << "Alerta: O arquivo" << file << "nao foi carreagdo pelon TileSet!" << std::endl;
        }
        else {
            //int imageWidth = tileSet.GetWidth(); 
            //int imageHeight = tileSet.GetHeight();
            int imageWidth, imageHeight;
            SDL_QueryTexture(tileSet.GetTexture(), nullptr, nullptr, &imageWidth, &imageHeight);
            std::cout << "LOG: Tileset carregado com sucesso! Tamanho: " << imageWidth << "x" << imageHeight << std::endl;

            int columns = imageWidth / tileWidth;
            int rows = imageHeight / tileHeight;

            tileSet.SetFrameCount(columns, rows); 

            this->tileCount = columns * rows;

        }
        tileSet.SetCameraFollower(true);
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

