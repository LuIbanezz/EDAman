#include "Cyan.h"

Cyan::Cyan(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot4");
}

Cyan::~Cyan()
{
    mqttClient->disconnect();
}
    
void Cyan::start()
{

    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(21);
    setEyes(SKYBLUE, SKYBLUE);
}

void Cyan::update(float deltaTime)
{
    
}

void Cyan::calculateObjectiveTile()
{

}