#include "../include/TileMap.h"
#include "../include/Camera.h"
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated){
    SetTileSet(tileSet);
    Load(file);

    for (int i = 0; i < mapDepth; i++) {
        parallax.push_back(1.0f);
    }
}

void TileMap::Load(std::string file) {
    std::ifstream mapFile(file);

    if (!mapFile.is_open()) {
        std::cout << "Erro: Nao foi possivel abrir o arquivo de mapa:" << file << std::endl;
        return;
    }

    char separator;
    mapFile >> mapWidth >> separator >> mapHeight >> separator >> mapDepth >> separator;

    parallax.resize(mapDepth, 1.0f);

    tileMatrix.clear();

    int tile;

    while (mapFile >> tile) {
        tileMatrix.push_back(tile);
        mapFile >> separator;
    }

    std::cout << "Mapa carregado: " << mapWidth << "x" << mapHeight << " Camadas: " << mapDepth << std::endl;
    std::cout << "Total de tiles no vetor: " << tileMatrix.size() << std::endl;

}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[x + y * mapWidth +  z * ( mapHeight * mapWidth ) ];
}

void TileMap::RenderLayer(int layer) {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int index = At(x, y, layer);

            if (index == -1) continue;

            //Tile Mundo
            float posX = associated.box.x + x * tileSet->GetTileWidth();
            float posY = associated.box.y + y * tileSet->GetTileHeight();

            //Aplicando Parallax
            float finalX = posX  - (Camera::pos.x * parallax[layer]);
            float finalY = posY  - (Camera::pos.y * parallax[layer]);

            tileSet->RenderTile(index, finalX, finalY);
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

void TileMap::Update(float dt){

}

void TileMap::SetParallax(int layer, float factor){
    if (layer >= 0 && layer < mapDepth) {
        parallax[layer] = factor;
    }
}
