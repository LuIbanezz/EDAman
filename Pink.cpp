#include "Pink.h"


Pink::Pink(MQTTClient &mqttClient, GameModel &gameModel)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    robotId = std::string("robot3");
}

Pink::~Pink()
{
    mqttClient->disconnect();
}
    
void Pink::start()
{

    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(0);
    setEyes(PINK, PINK);
}

void Pink::update(float deltaTime)
{
    
}