#include "Cyan.h"

Cyan::Cyan(MQTTClient &mqttClient, GameModel &gameModel, Player &player, Red &red)
{
    this->mqttClient = &mqttClient;
    this->gameModel = &gameModel;
    this->player = &player;
    this->red = &red;
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

    isMoving = false;
	// dispersionTile = { 0, 36 + 2 };   // TODO: ver MAZE_HEIGHT

    // float aux = GetTime();
    // while (GetTime() - aux < 1.5) {
    //     ;
    // }
}

void Cyan::update(float deltaTime)
{
    if (gameModel->getRemainingDots() <= 175) //el 30 es solo por ahora, no conté la cantidad de remaining dots que hay, pero tiene  
    {                                        //que empezar cuando el jugador haya comido 60 dots
        if (!isMoving)
		{
			exitCage();
		}
		else
		{
			calculateObjectiveTile();
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