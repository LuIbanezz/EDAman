#include "Red.h"

Red::Red(MQTTClient &mqttClient, GameModel &gameModel)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    robotId = std::string("robot2");
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
}

void Red::update(float deltaTime)
{
    
}