#include "Game.h"
#include <iostream>
//Factories
#include "SandFactory.h"
#include "WaterFactory.h"
#include "WallFactory.h"
#include "LavaFactory.h"

//Create factories for each material and store their behaviours in the vector
void Game::initializeBehaviours()
{
    SandFactory sandFactory;
    WaterFactory waterFactory;
	WallFactory wallFactory;
	LavaFactory lavaFactory;

	behaviours.resize(static_cast<int>(Material::COUNT));

    behaviours[static_cast<int>(Material::SAND)] = sandFactory.createBehaviour();
    behaviours[static_cast<int>(Material::WATER)] = waterFactory.createBehaviour();
	behaviours[static_cast<int>(Material::WALL)] = wallFactory.createBehaviour();
	behaviours[static_cast<int>(Material::LAVA)] = lavaFactory.createBehaviour();
}


Game::Game()
    : window(sf::VideoMode({ GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE }), "Falling Sand"), grid(GRID_HEIGHT, GRID_WIDTH) {

    //UI adjustments
    const char* fontfilePath = "Roboto-Regular.ttf";
    sf::Vector2f textPos = sf::Vector2f(10, 10);
    
    if (font.openFromFile(fontfilePath)) {
        uiText.emplace(font);
        uiText->setString(" 1 - Sand\n 2 - Water\n 3 - Wall \n 4 - Lava");
        uiText->setPosition(textPos);
    }

    //Time adjustments
    elapsedTime = 0;
    step = 1.f / STEP_PER_SECOND;

    //Gameplay Adjustments
    currentMaterial = Material::SAND;
	initializeBehaviours();
}

void Game::run()
{

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        handleInput();
        update();
        render();
    }
}

void Game::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) currentMaterial = Material::SAND;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) currentMaterial = Material::WATER;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) currentMaterial = Material::WALL;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) currentMaterial = Material::LAVA;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        int cellX = mousePos.x / CELL_SIZE;
        int cellY = mousePos.y / CELL_SIZE;

        if (cellX >= 0 && cellX < GRID_WIDTH &&
            cellY >= 0 && cellY < GRID_HEIGHT)
        {
            grid.addCell(cellX, cellY, (int)currentMaterial);
        }
    }
}

void Game::update()
{
    float oneIterationTime = clock.restart().asSeconds();
    elapsedTime += oneIterationTime;

    if (elapsedTime >= step) {
		grid.update(behaviours);
        elapsedTime -= step;
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);
    grid.drawGrid(window, CELL_SIZE);
    if (uiText) {
        window.draw(*uiText);
    }
    window.display();
}


