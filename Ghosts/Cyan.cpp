#include "Cyan.h"

Cyan::Cyan(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot4");
}

Cyan::~Cyan()
{
    mqttClient->disconnect();
}
    
void Cyan::start()
{
    setDisplay(21);
    setEyes(SKYBLUE, SKYBLUE);

    setpoint = getSetpoint({12, 17});
	setSetpoint(setpoint);
    setpoint.rotation = ROTATION_UP;
}

void Cyan::update(float deltaTime)
{
    
}

void Cyan::calculateObjectiveTile()
{

}