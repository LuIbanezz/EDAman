#include "Pink.h"


Pink::Pink(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot3");
}

Pink::~Pink()
{
    mqttClient->disconnect();
}
    
void Pink::start()
{
    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(19);
    setEyes(PINK, PINK);
}

void Pink::update(float deltaTime)
{
    
}

void Pink::calculateObjectiveTile()
{
    
}