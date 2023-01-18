#include <SFML/Graphics.hpp>
using namespace sf;

#include "Terrain/ChunkManager.h"

#include <iostream>

int main() {
    RenderWindow window(VideoMode(800, 600), "Marching Squares");

    Clock timer;
    View view = window.getDefaultView();
    window.setView(view);
    bool dragging = false;
    float zoom = 1.f;
    Vector2f mouseOldPos = Vector2f();
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
            case Event::Closed: {
                window.close();
                break;
            }
            case Event::MouseButtonPressed: {
                if (e.mouseButton.button == Mouse::Button::Left) dragging = true;
                mouseOldPos = window.mapPixelToCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));
                break;
            }
            case Event::MouseButtonReleased: {
                if (e.mouseButton.button == Mouse::Button::Left) dragging = false;
                break;
            }
            case Event::MouseMoved: {
                if (!dragging)
                    break;

                sf::Vector2f mouseCurrentPos = window.mapPixelToCoords(sf::Vector2i(e.mouseMove.x, e.mouseMove.y));
                sf::Vector2f deltaPos = mouseOldPos - mouseCurrentPos;

                view.setCenter(view.getCenter() + deltaPos);
                window.setView(view);

                mouseOldPos = window.mapPixelToCoords(sf::Vector2i(e.mouseMove.x, e.mouseMove.y));
                break;
            }
            case Event::MouseWheelScrolled: {
                if (e.mouseWheelScroll.delta <= -1)
                    zoom = std::min(2.f, zoom + .1f);
                else if (e.mouseWheelScroll.delta >= 1)
                    zoom = std::max(.5f, zoom - .1f);

                view.setSize(window.getDefaultView().getSize());
                view.zoom(zoom);
                window.setView(view);
                break;
            }
            }
        }
        float deltaTime = timer.restart().asSeconds();
        window.clear();
        window.display();
    }
}
