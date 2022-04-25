#include "Red.h"

Red::Red(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot2");

    objectiveTile = {0, 0};
    dispersionTile = {28-2,-2}; //MAZE_WIDTH - 2, -2
    lastDirection = 1;
    newDirection = 0;
}

Red::~Red()
{
    mqttClient->disconnect();
}

void Red::start()
{
    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(17);
    setEyes(RED, RED);

    setpoint.rotation = ROTATION_LEFT;
    setpoint = getSetpoint({14, 14});
    setSetpoint(setpoint);

    float aux = GetTime();
    while (GetTime() - aux < 1.5) {
        ;
    }
}

void Red::update(float deltaTime)
{
    if (gameModel->getGameTime() > 0)   //automaticamente al tocar una tecla Game time ser� mayor a 0 ent el rojo perseguir�
    { 
        if (setpoint.position.x == 14 && setpoint.position.x == 17)
        {
            exitCage();
            dead = false;
        }
        else if (!dead)
        {
            switch(gameModel->getGameState())
            {
                case(Persecution):
                    calculateObjectiveTile();
                    break;
                case(Dispersion):
                    objectiveTile = dispersionTile;
                    break;
                case(Blue):
                    calculateBlueObjectiveTile();
                    break;
            }

            calculateNewDirection();
            move(deltaTime);
        }
        else
        {
            calculateNewDirection();
            move(deltaTime);
        }
    }
}

void Red::calculateObjectiveTile()
{
    objectiveTile = player->getPlayerPosition();
}

Vector2 Red::getRedTile()
{
    return  getTilePosition(setpoint);
}