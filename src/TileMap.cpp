#include "../include/TileMap.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated){
    SetTileSet(tileSet);
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream mapFile(file);

    mapFile >> mapWidth >> mapHeight >> mapDepth;

    tileMatrix.clear();

    int tile;

    for ( int i = 0; i < mapWidth * mapHeight * mapDepth; i++) {
        mapFile >> tile;
        tileMatrix.push_back(tile);
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}

void TileMap::RenderLayer(int layer) {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int index = At(x, y, layer);

            if (index == -1) {
                continue;
            }

            tileSet->RenderTile(
                    index, 
                    associated.box.x + x * tileSet->GetTileWidth(),
                    associated.box.y + y * tileSet->GetTileHeight()
                    );
        }
    }
}

void TileMap::Render() {
    for (int i = 0; i < mapDepth; i++) {
        RenderLayer(i);
    }
}

    int TileMap::GetWidth(){
        return mapWidth;
    }

    int TileMap::GetHeight(){
        return mapHeight;
    }

    int TileMap::GetDepth(){
        return mapDepth;
    }
