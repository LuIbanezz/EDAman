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
    if(!(mqttClient->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez")))
    {
        std::cout << "No se logró establecer la conexión" << std::endl;
    }

    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(17);
}

void Red::update(float deltaTime)
{
    
}