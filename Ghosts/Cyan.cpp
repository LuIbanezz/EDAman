#include "Cyan.h"

Cyan::Cyan(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot3");
}

Cyan::~Cyan()
{
    mqttClient->disconnect();
}
    
void Cyan::start()
{
    setDisplay(21);
    setEyes(SKYBLUE, SKYBLUE);

    setpoint.rotation = ROTATION_UP;
    setpoint = getSetpoint({12, 17});
	setSetpoint(setpoint);

    // float aux = GetTime();
    // while (GetTime() - aux < 1.5) {
    //     ;
    // }
}

void Cyan::update(float deltaTime)
{
    if (gameModel->getRemainingDots() <= 175) //el 30 es solo por ahora, no conté la cantidad de remaining dots que hay, pero tiene  
    {                                        //que empezar cuando el jugador haya comido 60 dots
        calculateObjectiveTile();
        calculateNewDirection();
        move(deltaTime);
    }
}

void Cyan::calculateObjectiveTile() //TODO
{

}