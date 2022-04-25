#include "Orange.h"

Orange::Orange(MQTTClient& mqttClient, GameModel& gameModel, Player& player)
{
	this->mqttClient = &mqttClient;
	this->gameModel = &gameModel;
	this->player = &player;
	robotId = std::string("robot5");

	dispersionTile = { 0, 30 };   // TODO: ver MAZE_HEIGHT
    isMoving = false;
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
	setpoint = getSetpoint({ 16, 17 });
	setSetpoint(setpoint);
}

void Orange::update(float deltaTime)
{
	if (gameModel->getRemainingDots() <= 205)   // tiene que empezar cuando el jugador haya comido 30 dots  
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
			//std::cout << "direccion:" << newDirection << std::endl;
            move(deltaTime);
		}
		else
        {
            calculateNewDirection();
            move(deltaTime);
        }
	}
}

void Orange::calculateObjectiveTile() //TODO
{
	float norm = Vector2Length(Vector2Subtract(player->getPlayerPosition(), getTilePosition(setpoint)));

	if (norm >= 8)
	{
		objectiveTile = player->getPlayerPosition();
	}
	else
	{
		objectiveTile = dispersionTile;
	}
}