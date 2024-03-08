#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>  
#include "GameStateManager.h"
#include "GridGenerator.h"
#include <iostream>
#include <set>
#include "InputStateManager.h"
#include "InputState.h"

class Camera {
public:
    Camera();

    bool Update();
    void Draw(std::vector<sf::Sprite> sprites);

    void WorldToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY);
    void ScreenToWorld(int screenX, int screenY, float& outWorldX, float& outWorldY);
    void MinimapToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY);
    void Zoom(sf::Event& event);


    sf::RenderWindow window;
    sf::RenderTexture renderTexture;
    sf::RenderTexture minimapTexture;

    float screenRatio = 0.f;
    float offsetX = 0.f;
    float offsetY = 0.f;
    float minimapscaleX = 0.3f;
    float minimapscaleY = 0.3f;
    float scaleX = 1.f;
    float scaleY = 1.f;
private:
    sf::View view;

    bool mouseButtonPanning = false;
    bool edgePanning = false;

    float startPanX = 0.f;
    float startPanY = 0.f;

    float worldX = 0.f;
    float worldY = 0.f;

    int screenX = 0.f;
    int screenY = 0.f;
    sf::Texture terrainTexture;
    void renderMainMap(std::vector<sf::Sprite> sprites);
    void renderMiniMap(std::vector<sf::Sprite> sprites);
    void clickPan(const InputState& inputState);
    void scrollPan(const InputState& inputState);
    void snapPan(const InputState& inputState);
};
