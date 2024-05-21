#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "../include/scene.hpp"
#include "../include/utilities.hpp"
#include "../include/game.hpp"



using json = nlohmann::json;

Param Scene::set_param(SDL_Rect pos, SDL_RendererFlip flip, int rotation) {
        Param param;
        param.pos = pos;
        param.flip = flip;
        param.rotation = rotation;
        return param;
    }

Clip Scene::set_clip(SDL_Rect clip, vector<Param> params) {
    Clip newClip;
    newClip.clip = clip;
    newClip.params = params;
    return newClip;
}

Tiles Scene::set_tiles(SDL_Texture *asset, std::vector<Clip> clips) {
    Tiles tiles;
    tiles.asset = asset;
    tiles.clips = clips;
    return tiles;
}


void Scene::load_scene(const std::string& jsonFilePath) {
    // Open the JSON file
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file: " << jsonFilePath << std::endl;
        return;
    }

    // Renderer to create Texture
    SDL_Renderer *renderer = Game::appWindow->renderer;

    // Load JSON data
    json j;
    file >> j;

    // Load assets
    if (j.contains("assests")) {
        auto assets = j["assests"];

        for (auto& assetGroup : assets) {
            for (auto& assetItem : assetGroup.items()) {
                std::string assetName = assetItem.key();
                auto assetData = assetItem.value();

                // Load the image
                std::string imagePath = assetData[0]["path"];
                SDL_Surface* image = IMG_Load(imagePath.c_str());
                if (!image) {
                    std::cerr << "Error loading image: " << imagePath << std::endl;
                    continue;
                }

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);

                // Parse clips
                int clipIndex = 0;
                while (true) {
                    std::string clipsKey = "clips" + std::to_string(clipIndex);
                    if (!assetData[0].contains(clipsKey)) {
                        break; // No more clips for this asset
                    }

                    std::vector<Clip> clips;
                    for (auto& clipData : assetData[0][clipsKey]) {
                        SDL_Rect clipRect;
                        clipRect.x = clipData["clip"][0]["x"];
                        clipRect.y = clipData["clip"][0]["y"];
                        clipRect.w = clipData["clip"][0]["w"];
                        clipRect.h = clipData["clip"][0]["h"];

                        std::vector<Param> params;
                        for (auto& position : clipData["positions"]) {
                            for (auto& tile : position.items()) {
                                for (auto& paramData : tile.value()) {
                                    SDL_Rect posRect;
                                    posRect.x = paramData["pos"][0]["x"];
                                    posRect.y = paramData["pos"][0]["y"];
                                    posRect.w = paramData["pos"][0]["w"];
                                    posRect.h = paramData["pos"][0]["h"];

                                    SDL_RendererFlip flip = SDL_FLIP_NONE;
                                    std::string flipStr = paramData["parameters"][0]["flip"];
                                    if (flipStr == "SDL_FLIP_HORIZONTAL") {
                                        flip = SDL_FLIP_HORIZONTAL;
                                    } else if (flipStr == "SDL_FLIP_VERTICAL") {
                                        flip = SDL_FLIP_VERTICAL;
                                    }

                                    int rotation = paramData["parameters"][0]["angle"];
                                    int ratio = paramData["parameters"][0]["ratio"];

                                    // Modify position rectangle based on ratio
                                    posRect.w *= ratio;
                                    posRect.h *= ratio;

                                    Param param = set_param(posRect, flip, rotation);
                                    params.push_back(param);
                                }
                            }
                        }

                        Clip clip = set_clip(clipRect, params);
                        clips.push_back(clip);
                    }

                    // Create Tiles object and add to assets
                    Tiles tiles = set_tiles(texture, clips);
                    assests.push_back(tiles);

                    clipIndex++;
                }
            }
        }
    }

    // Load bounding boxes
    if (j.contains("bounding_box")) {
        auto boundingBoxes = j["bounding_box"];

        // Iterate over each bounding box group
        for (auto& bboxGroup : boundingBoxes) {
            for (auto& bboxItem : bboxGroup.items()) {
                auto boxesData = bboxItem.value();
                for (auto& box : boxesData) {
                    SDL_Rect rect;
                    rect.x = box["x"];
                    rect.y = box["y"];
                    rect.w = box["w"];
                    rect.h = box["h"];
                    boxes.push_back(rect);
                }
            }
        }
    }
}

void Scene::drawScene() {
    // Calculate scaling factors
    SDL_Renderer *renderer = Game::appWindow->renderer;
    float scaleX = static_cast<float>(Game::appWindow->WIDTH) / 1366;
    float scaleY = static_cast<float>(Game::appWindow->HEIGHT) / 768;

    // Set the scaling for the renderer
    SDL_RenderSetScale(renderer, scaleX, scaleY);

    // Iterate over each Tiles object in the assets vector
    for (const auto& tiles : assests) {
        // Iterate over each Clip object in the clips vector
        for (const auto& clip : tiles.clips) {
            // Iterate over each Param object in the params vector
            for (const auto& param : clip.params) {
                // Render the texture using SDL_RenderCopyEx
                SDL_RenderCopyEx(renderer, tiles.asset, &clip.clip, &param.pos, param.rotation, nullptr, param.flip);
            }
        }
    }

    // draw_boxes();

    SDL_RenderSetScale(renderer, 1.0f, 1.0f);
}

void Scene::draw_boxes() {
    SDL_Renderer *renderer = Game::appWindow->renderer;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (const auto& box : boxes) {
        SDL_RenderDrawRect(renderer, &box);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

