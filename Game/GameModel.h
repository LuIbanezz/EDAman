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

#ifndef _GAMEMODEL_H
#define _GAMEMODEL_H

class Robot;

/**
 * @brief Game state
 * 
 */
enum GameState
{
    Dispersion,
    Persecution,
    Blue
};

#include <string>
#include <list>
#include <vector>

#include <raylib.h>

#include "../MQTTClient.h"

#include "GameView.h"
#include "../Robot.h"

class GameModel
{
public:
    GameModel(MQTTClient *mqttClient);

    void setGameView(GameView *gameView);

    void addRobot(Robot *robot);

    void start();
    void update(float deltaTime);

    bool isTileFree(Vector2 position);
    void eat(Vector2 tilePosition);

    void setGameTime(float time);    
    float getGameTime();

    int getRemainingDots();

    int getGameState();
    void setGameState(int gameState);

    void setMaze(std::string maze);

    void setViewMessage(int value);

private:

    void checkCollision();
    void deathEDAMAN();
    
    MQTTClient *mqttClient;
    GameView *gameView;

    std::string maze;
    std::string originalMaze;
    std::vector<Robot *> robots;

    int gameState;
    float gameStateTime;

    float gameTime;    
    float auxTimer; 

    int remainingDots;
    int remainingEnergizers;
    int enemiesEaten;

    unsigned int highScore;
    unsigned int score;
    unsigned int lastScore;

    int lives;
    std::list<int> eatenFruits;
};

#endif
