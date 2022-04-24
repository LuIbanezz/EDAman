#include "Orange.h"

Orange::Orange(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot5");
    
    // TODO
    // displayImages = LoadImage("RobotImages.png");
}

Orange::~Orange()
{
    mqttClient->disconnect();
}
    
void Orange::start()
{
    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(23);
    setEyes(ORANGE, ORANGE);
    setpoint.rotation = ROTATION_UP;
    setpoint = getSetpoint({16, 17});
    setSetpoint(setpoint);
    
}

void Orange::update(float deltaTime)
{
    
}

void Orange::calculateObjectiveTile()
{
    
}