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
    if(!(mqttClient->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez")))
    {
        std::cout << "No se logr� establecer la conexi�n" << std::endl;
    }

    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(23);
}

void Orange::update(float deltaTime)
{
    
}