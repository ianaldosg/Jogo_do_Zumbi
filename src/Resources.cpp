#include "../include/Resources.h"
#include "../include/Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);

    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (texture == nullptr) {
        printf("Erro ao carregar imagem: %s\n", SDL_GetError());
        return nullptr;
    }

    std::shared_ptr<SDL_Texture> sharedTexture(
            texture,
            [] (SDL_Texture* t) { SDL_DestroyTexture(t); }
            );

    imageTable[file] = sharedTexture;
    return sharedTexture;
}

void Resources::ClearImages() {
    auto it = imageTable.begin();
    while (it != imageTable.end()) {
        if (it->second.use_count() == 1) {
            it = imageTable.erase(it);
        } else {
            ++it;
        }
    }
    //for (auto& pair : imageTable) {
    //    if (pair.second != nullptr) {
    //        SDL_DestroyTexture(pair.second);
    //    }
    //}

    //imageTable.clear();
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);

    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        printf("Erro ao carregar musica: %s\n", Mix_GetError());
        return nullptr;
    }

    std::shared_ptr<Mix_Music> sharedMusic(
            music,
            [] (Mix_Music* m) { Mix_FreeMusic(m); }
            );


    musicTable[file] = sharedMusic;

    return sharedMusic;
}

void Resources::ClearMusic() {
    auto it = musicTable.begin();
    while (it != musicTable.end()) {
        if (it->second.use_count() == 1) {
            it = musicTable.erase(it);
        } else {
            ++it;
        }
    }
    //for (auto& pair : musicTable) {
    //    Mix_FreeMusic(pair.second);
    //}

    //musicTable.clear();
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);

    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());

    if (chunk == nullptr) {
        printf("Erro ao carregar som: %s\n", Mix_GetError());
        return nullptr;
    }

    std::shared_ptr<Mix_Chunk> sharedChunk(
            chunk,
            [] (Mix_Chunk* c) { Mix_FreeChunk(c); }
            );

    soundTable[file] = sharedChunk;
    return sharedChunk;
}

void Resources::ClearSounds() {
    auto it = soundTable.begin();
    while (it != soundTable.end()) {
        if (it->second.use_count() == 1) {
            it = soundTable.erase(it);
        } else {
            ++it;
        }
    }
    //for (auto& pair : soundTable) {
    //    Mix_FreeChunk(pair.second);
    //}

    //soundTable.clear();
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int size) {
    std::string key = file + std::to_string(size);

    auto it = fontTable.find(key);
    if (it != fontTable.end()) {
        return it->second;
    }

    TTF_Font* font = TTF_OpenFont(file.c_str(), size);
    if (font == nullptr) {
        printf("Erro ao carregar fonte: %s", TTF_GetError());
        return nullptr;
    }

    std::shared_ptr<TTF_Font> sharedFont(
            font,
            [] (TTF_Font* f) { TTF_CloseFont(f); }
            );

    fontTable[key] = sharedFont;
    return sharedFont;
}

void Resources::ClearFonts() {
    auto it = fontTable.begin();
    while (it != fontTable.end()) {
        if (it->second.use_count() == 1) {
            it = fontTable.erase(it);
        } else {
            ++it;
        }
    }
    //for (auto& pair : fontTable) {
    //    TTF_CloseFont(pair.second);
    //}
    //fontTable.clear();
}
