#include "Cyan.h"

Cyan::Cyan(MQTTClient &mqttClient, GameModel &gameModel, Player &player, Red &red)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    this->red = &red;
    robotId = std::string("robot4");

    dispersionTile = {28, 36 + 2};
    isMoving = false;
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
}

void Cyan::update(float deltaTime)
{
    if (gameModel->getRemainingDots() <= 175) //el 30 es solo por ahora, no conté la cantidad de remaining dots que hay, pero tiene  
    {                                        //que empezar cuando el jugador haya comido 60 dots
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

void Cyan::calculateObjectiveTile()
{
    Vector2 playerPosition;

    switch (player->getPlayerDirection())
    {
    case (0):
        playerPosition = Vector2Subtract(player->getPlayerPosition(), {0, 2});
        break;
    case (1):
        playerPosition = Vector2Subtract(player->getPlayerPosition(), {2, 0});
        break;
    case (2):
        playerPosition = Vector2Add(player->getPlayerPosition(), {0, 2});
        break;
    case (3):
        playerPosition = Vector2Add(player->getPlayerPosition(), {2, 0});
        break;
    }

    Vector2 directionVector = Vector2Subtract(playerPosition, red->getRedTile());

    objectiveTile = Vector2Add(directionVector, playerPosition);
}