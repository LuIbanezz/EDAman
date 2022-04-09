#include "Orange.h"

Orange::Orange(MQTTClient &mqttClient, GameModel &gameModel)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
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
}

void Orange::update(float deltaTime)
{
    
}