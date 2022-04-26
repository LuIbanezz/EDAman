#include "Red.h"

Red::Red(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot2");

    dispersionTile = {28-2,-2}; //MAZE_WIDTH - 2, -2
    lastDirection = 1;
    newDirection = 0;
}

Red::~Red()
{
    mqttClient->disconnect();
}

void Red::start()
{
    setDisplay(17);
    setEyes(RED, RED);

    setpoint.rotation = ROTATION_RIGHT;
    setSetpoint(getSetpoint({14, 14}));
    objectiveTile = { 14, 14 };

    isMoving = true;
}

void Red::update(float deltaTime)
{
    if (gameModel->getGameTime() > 0)   //automaticamente al tocar una tecla Game time será mayor a 0 ent el rojo perseguirá
    { 
		ghostState(deltaTime);
    }
}

void Red::calculateObjectiveTile()
{
    objectiveTile = player->getPlayerPosition();
}

Vector2 Red::getRedTile()
{
    return  getTilePosition(setpoint);
}