#include "Orange.h"

Orange::Orange(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
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
    setpoint.rotation = ROTATION_UP;
    setpoint = getSetpoint({16, 17});
    setSetpoint(setpoint);

    // float aux = GetTime();
    // while (GetTime() - aux < 1.5) {
    //     ;
    // }
}

void Orange::update(float deltaTime)
{
    if (gameModel->getRemainingDots() <= 205) //el 50 es solo por ahora, no conté la cantidad de remaining dots que hay, pero tiene  
    {                                        //que empezar cuando el jugador haya comido 30 dots
        calculateObjectiveTile();
        calculateNewDirection();
        move(deltaTime);
    }
}

void Orange::calculateObjectiveTile() //TODO
{
    
}