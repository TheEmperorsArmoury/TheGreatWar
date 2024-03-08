#include "Camera.h"
#include<iostream>

Camera::Camera()
    : window(sf::VideoMode::getDesktopMode(), "The Great War", sf::Style::Fullscreen) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);
    if (!renderTexture.create(2000, 2000));
    if (!minimapTexture.create(500, 500));
    if (!terrainTexture.create(500, 500));
    
    sf::Vector2u screenSize = renderTexture.getSize();
    int screensizex = screenSize.x;
    int screensizey = screenSize.y;
   
   offsetX = -(screenSize.x / 2.0f);
    //offsetX = -(500 / 2.0f);
    offsetY = -(screenSize.y / 2.0f);
    //offsetY = -(500 / 2.0f);
    
}

bool Camera::Update() {
    sf::Event event;

    const InputState& inputState = InputStateManager::getInstance().getInputState();

    if (inputState.isEscapePressed) {
        return false;
    }

    clickPan(inputState);
    scrollPan(inputState);
    snapPan(inputState);

    return true;
}

void Camera::Zoom(sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float worldXBeforeZoom, worldYBeforeZoom;
        ScreenToWorld(mousePos.x, mousePos.y, worldXBeforeZoom, worldYBeforeZoom);

        if (event.mouseWheelScroll.delta > 0) {
            scaleX *= 1.05f;
            scaleY *= 1.05f;
        }
        else if (event.mouseWheelScroll.delta < 0) {
            scaleX *= 0.95f;
            scaleY *= 0.95f;
        }

        bool scaleChanged = false;

        if (scaleX > 2.0f) scaleX = 2.0f;
        else if (scaleX < 0.5f) scaleX = 0.5f;
        else scaleChanged = true;

        if (scaleY > 2.0f) scaleY = 2.0f;
        else if (scaleY < 0.5f) scaleY = 0.5f;
        else scaleChanged = true;

        if (scaleChanged) {
            float worldXAfterZoom, worldYAfterZoom;
            ScreenToWorld(mousePos.x, mousePos.y, worldXAfterZoom, worldYAfterZoom);

            offsetX += worldXBeforeZoom - worldXAfterZoom;
            offsetY += worldYBeforeZoom - worldYAfterZoom;
        }
    }
}
void Camera::MinimapToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY)
{
    outScreenX = (int)(worldX)*minimapscaleX;
    outScreenY = (int)(worldY)*minimapscaleY;
    if (worldX == 0) { std::cout << "position to 0" << std::endl;
    std::cout << offsetX << std::endl;
    }
}
void Camera::WorldToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY)
{
    outScreenX = (int)((worldX - offsetX) * scaleX);
    outScreenY = (int)((worldY - offsetY) * scaleY);
}

void Camera::ScreenToWorld(int screenX, int screenY, float& outWorldX, float& outWorldY)
{
    outWorldX = ((float)screenX / scaleX) + offsetX;
    outWorldY = ((float)screenY / scaleY) + offsetY;
}

void Camera::clickPan(const InputState& inputState) {
    sf::Vector2i mousePos = inputState.mousePosition;
    sf::Vector2u windowSize = window.getSize();

    if (inputState.isMiddleMouseButtonPressed) {
        if (!mouseButtonPanning) {
            mouseButtonPanning = true;
            startPanX = mousePos.x;
            startPanY = mousePos.y;
        }
        else {
            offsetX -= (mousePos.x - startPanX) / scaleX;
            offsetY -= (mousePos.y - startPanY) / scaleY;

            startPanX = mousePos.x;
            startPanY = mousePos.y;
        }
    }
    else {
        mouseButtonPanning = false;
    }
}

void Camera::scrollPan(const InputState& inputState) {
    const int edgeThreshold = 150;
    sf::Vector2i mousePos = inputState.mousePosition;
    sf::Vector2u windowSize = window.getSize();

    float panSpeedX = 0.0f;
    float panSpeedY = 0.0f;

    if (mousePos.x <= edgeThreshold)
        panSpeedX = (edgeThreshold - mousePos.x) / (static_cast<float>(edgeThreshold) * scaleX);
    else if (mousePos.x >= static_cast<int>(windowSize.x) - edgeThreshold)
        panSpeedX = -(mousePos.x - (static_cast<int>(windowSize.x) - edgeThreshold)) / (static_cast<float>(edgeThreshold) * scaleX);

    if (mousePos.y <= edgeThreshold)
        panSpeedY = (edgeThreshold - mousePos.y) / (static_cast<float>(edgeThreshold) * scaleY);
    else if (mousePos.y >= static_cast<int>(windowSize.y) - edgeThreshold)
        panSpeedY = -(mousePos.y - (static_cast<int>(windowSize.y) - edgeThreshold)) / (static_cast<float>(edgeThreshold) * scaleY);

    if (panSpeedX != 0.0f || panSpeedY != 0.0f) {
        offsetX -= panSpeedX * 10;
        offsetY -= panSpeedY * 10;
    }
}


void Camera::snapPan(const InputState& inputState)
{
    //Once there are scenery and units on the battlefield, snap panning will be possible via hotkeys, snapping the camera to the position of a unit.
}
void Camera::renderMainMap(std::vector<sf::Sprite> sprites) {
    int centerOffsetX = renderTexture.getSize().x / 2;
    for (sf::Sprite s : sprites) {
        int screenX, screenY;
        WorldToScreen(s.getPosition().x + centerOffsetX, s.getPosition().y, screenX, screenY);
       
        s.setPosition(static_cast<float>(screenX), static_cast<float>(screenY));
        s.setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));


        renderTexture.draw(s);
    }
}
void Camera::renderMiniMap(std::vector<sf::Sprite> sprites) {
    int minimapcenterOffsetX = minimapTexture.getSize().x / 2;

    for (sf::Sprite s : sprites) {
        int screenX, screenY;
       
        MinimapToScreen(s.getPosition().x + minimapcenterOffsetX, s.getPosition().y, screenX, screenY);
        s.setColor(sf::Color(0, 255, 0));
        s.setPosition(static_cast<float>(screenX+150), static_cast<float>(screenY));
        s.setScale(static_cast<float>(minimapscaleX), static_cast<float>(minimapscaleY));
        // s.setRotation(-45);



        minimapTexture.draw(s);
    }
}
void Camera::Draw(std::vector<sf::Sprite> sprites) {
    window.clear(sf::Color::Black);
    renderTexture.clear(sf::Color::Black);
    minimapTexture.clear(sf::Color::Transparent);
  
    int centerOffsetX = renderTexture.getSize().x / 2;
    int minimapcenterOffsetX = minimapTexture.getSize().x / 2;
      
    renderMainMap(sprites);
    renderMiniMap(sprites);
  
    minimapTexture.display();
    renderTexture.display();
   
    //create textures for minimap and main game 
    const sf::Texture& texture = renderTexture.getTexture();
    const sf::Texture& minimaptexture = minimapTexture.getTexture();
    // draw it to the window
    
   
    sf::Sprite mapSprite(texture);
    sf::Sprite minimapSprite(minimaptexture);
    sf::Vector2u screenSize = window.getSize();
    float screensizex = screenSize.x;
    float screensizey = screenSize.y;
    float screenratio = (screensizex) / (screensizey);
    mapSprite.setPosition(static_cast<float>(- 50), static_cast<float>(1));
    mapSprite.setScale(static_cast<float>(0.5 * screenratio), static_cast<float>(0.5));
    minimapSprite.setPosition(static_cast<float>(screenX + 1400), static_cast<float>(screenY + 675));
    minimapSprite.setScale(static_cast<float>(0.6), static_cast<float>(0.6));
   // minimapSprite.setRotation(45);
    //draw and display textures 
    window.draw(mapSprite);
    window.draw(minimapSprite);
    window.display();
}