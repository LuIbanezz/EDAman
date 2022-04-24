#include "Pink.h"

Pink::Pink(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot4");
}

Pink::~Pink()
{
    mqttClient->disconnect();
}
    
void Pink::start()
{
    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(19);
    setEyes(PINK, PINK);
    setpoint.rotation = ROTATION_UP;
    setpoint = getSetpoint({14, 17});
    setSetpoint(setpoint);
    float aux = GetTime();
    while (GetTime() - aux < 1.5) {
        ;
    }
}

void Pink::update(float deltaTime)
{
    if (gameModel->getGameTime() > 0) { //pink tambien está libre al inicio
        if (setpoint.position.x == 14 && setpoint.position.x == 17) {
            setpoint = getSetpoint({ 14, 14 });
            setSetpoint(setpoint);
        }
        calculateObjectiveTile();
        calculateNewDirection();
        move(deltaTime);
    }
}

void Pink::calculateObjectiveTile()
{
    objectiveTile = Vector2Add(player->getPlayerPosition(), {0,4});
}