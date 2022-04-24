/**
 * @file GameModel.h
 * @author Marc S. Ressl
 * @brief EDA-Man game model
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include <raylib.h>
#include "raymath.h"
#include "GameModel.h"

using namespace std;

const int MAZE_WIDTH = 28;
const int MAZE_HEIGHT = 36;
const int MAZE_SIZE = MAZE_WIDTH * MAZE_HEIGHT;

/**
 * @brief Construct a new Game Model:: Game Model object
 * 
 * @param mqttClient An MQTTClient object
 */
GameModel::GameModel(MQTTClient *mqttClient)
{
    this->mqttClient = mqttClient;
    
    remainingDots = 0;
    remainingEnergizers = 0;
}

/**
 * @brief Setter for the GameView.
 * 
 * @param gameView A GameView object
 */
void GameModel::setGameView(GameView *gameView)
{
    this->gameView = gameView;
}

/**
 * @brief Adds a robot to the game model.
 * 
 * @param robot The robot
 */
void GameModel::addRobot(Robot *robot)
{
    robots.push_back(robot);
}

/**
 * @brief Resets game model to initial game conditions.
 * 
 * @param maze A maze
 */
void GameModel::start(string maze)
{
    this->maze = maze;
    this->maze.resize(MAZE_SIZE);

    for (auto c : maze)
    {
        if (c == '+')
            remainingDots++;
        else if (c == '#')
            remainingEnergizers++;
    }

    gameView->start(maze);

    lives = 4;
    eatenFruits.clear();

    gameState = Dispersion;
    gameTime = 0;

    gameView->setMessage(GameViewMessageReady);
    gameView->setLives(lives);
    gameView->setEatenFruits(eatenFruits);

    for (auto robot : robots)
        robot->start();

    // Just for testing
    gameView->playAudio("mainStart");
}

/**
 * @brief Updates game model for current frame.
 * 
 * @param deltaTime Number of seconds since the last frame
 */
void GameModel::update(float deltaTime)
{
    gameStateTime += deltaTime;

    for (auto robot : robots)
        robot->update(deltaTime);
}

/**
 * @brief Determine if a tile is free.
 * 
 * @param tilePosition A tile coordinate
 * @return true Tile is free
 * @return false Tile is not free
 */
bool GameModel::isTileFree(Vector2 tilePosition)
{
    if ((tilePosition.x < 0) || (tilePosition.x >= MAZE_WIDTH))
        return false;

    if ((tilePosition.y < 0) || (tilePosition.y >= MAZE_HEIGHT))
        return false;

    //tilePosition = Vector2Add(tilePosition, { 0.9,0.9 });

    char tile = maze[(int) (tilePosition.y)  * MAZE_WIDTH + (int)(tilePosition.x) ];

    return (tile == ' ') || (tile == '+') || (tile == '#');
}

void GameModel::eat(Vector2 tilePosition)
{
    char tile = maze[(int) (tilePosition.y)  * MAZE_WIDTH + (int)(tilePosition.x) ];

    if (tile == '+')
    {
        maze[(int) (tilePosition.y)  * MAZE_WIDTH + (int)(tilePosition.x) ] = ' ';
        gameView->clearTile(tilePosition.x, tilePosition.y);
        remainingDots--;
    }
    else if (tile == '#')
    {
        maze[(int) (tilePosition.y)  * MAZE_WIDTH + (int)(tilePosition.x) ] = ' ';
        gameView->clearTile(tilePosition.x, tilePosition.y);
        remainingEnergizers--;
        
       // gameState = Blue; //TODO
    }
}

void GameModel::setGameTime(float time)
{
    gameTime = time;
}  
    
float GameModel::getGameTime()
{
    return gameTime;
}

int GameModel::getRemainingDots() 
{
    return remainingDots;
}

int GameModel::getGameState()
{
    return gameState;
}

void GameModel::setGameState(int gameState) 
{
    this->gameState = gameState;
}