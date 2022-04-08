#include "Player.h"

Player::Player(MQTTClient &mqttClient, GameModel &gameModel)
{
    this->mqttClient = mqttClient;
    this->gameModel = gameModel;
    robotId = std::string("robot1");
}

Player::~Player()
{
    mqttClient->disconnect();
}
    
void Player::start()
{
    if(!(mqttClient->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez"))
    {
        std::cout << "No se logró establecer la conexión" << std::endl;
    }

    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(1);
}

void Player::update(float deltaTime)
{
    //vel que queremos m/s (fija(dato)) * 100 cm/m * deltaTime 
    //0.64 * 100 * delta time ===>sumamos en la coordenada X o Y
    //0.72 """"""
}