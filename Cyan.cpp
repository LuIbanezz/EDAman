#include "Cyan.h"

Cyan::Cyan(MQTTClient &mqttClient, GameModel &gameModel)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
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