#include "Red.h"

Red::Red(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot2");

    objectiveTile = {0, 0};
    lastDirection = 0;
    newDirection = 0;
}

Red::~Red()
{
    mqttClient->disconnect();
}

void Red::start()
{
    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(17);
    setEyes(RED, RED);

    setpoint.rotation = ROTATION_LEFT;
    setpoint = getSetpoint({14, 15});
    setSetpoint(setpoint);
}

void Red::update(float deltaTime)
{
    calculateObjectiveTile();
    calculateNewDirection();
    move(deltaTime);
}

void Red::calculateObjectiveTile()
{
    objectiveTile = player->getPlayerPosition();
}