#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Material.h"
#include <vector>
#include <memory>

class Game
{
public:
    Game();
    void run();

private:
    static constexpr int GRID_WIDTH = 240;
    static constexpr int GRID_HEIGHT = 120;
    static constexpr int CELL_SIZE = 5;
    static constexpr int STEP_PER_SECOND = 100;

    //Window
    sf::RenderWindow window;
    Grid grid;

    //Gameplay
    Material currentMaterial;
    std::vector<std::unique_ptr<MaterialBehaviour>> behaviours;  

    //Timing
    sf::Clock clock;
    float elapsedTime;
    float step;

    //UI
    sf::Font font;
    std::optional<sf::Text> uiText;

private:
	void initializeBehaviours();
    void handleInput();
    void update();
    void render();
};
