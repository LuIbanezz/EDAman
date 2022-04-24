#include "Orange.h"

Orange::Orange(MQTTClient& mqttClient, GameModel& gameModel, Player& player)
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
	setpoint = getSetpoint({ 16, 17 });
	setSetpoint(setpoint);

    isMoving = false;
	dispersionTile = { 0, 36 + 2 };   // TODO: ver MAZE_HEIGHT

	// float aux = GetTime();
	// while (GetTime() - aux < 1.5) {
	//     ;
	// }
}

void Orange::update(float deltaTime)
{
	if (gameModel->getRemainingDots() <= 205)   //tiene que empezar cuando el jugador haya comido 30 dots  
	{
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