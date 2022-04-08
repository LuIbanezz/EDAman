#include "Pink.h"


Pink::Pink(MQTTClient &mqttClient, GameModel &gameModel)
{
    this->mqttClient = mqttClient;
    this->gameModel = gameModel;
    robotId = std::string("robot1");
}

Pink::~Pink()
{
    mqttClient->disconnect();
}
    
void Pink::start()
{
    if(!(mqttClient->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez"))
    {
        std::cout << "No se logró establecer la conexión" << std::endl;
    }

    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(19);
}

void Pink::update(float deltaTime)
{
    
}