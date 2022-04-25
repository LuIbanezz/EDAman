#include "Pink.h"

Pink::Pink(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    robotId = std::string("robot3");

    dispersionTile = {2, -2};
    isMoving = false;
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
    liftTo({0, 0, 0});
    setpoint.rotation = ROTATION_UP;
    setpoint = getSetpoint({14, 17});
    setSetpoint(setpoint);


    // float aux = GetTime();
    // while (GetTime() - aux < 1.5)
    // {
    //     ;
    // }
}

void Pink::update(float deltaTime)
{
    if (gameModel->getGameTime() > 0) // pink tambien est� libre al inicio
    {
        if (!isMoving || (setpoint.position.x == 14 && setpoint.position.x == 17))
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

void Pink::calculateObjectiveTile()
{
    switch (player->getPlayerDirection())
    {
    case (0):
        objectiveTile = Vector2Subtract(player->getPlayerPosition(), {0, 4});
        break;
    case (1):
        objectiveTile = Vector2Subtract(player->getPlayerPosition(), {4, 0});
        break;
    case (2):
        objectiveTile = Vector2Add(player->getPlayerPosition(), {0, 4});
        break;
    case (3):
        objectiveTile = Vector2Add(player->getPlayerPosition(), {4, 0});
        break;
    }
}