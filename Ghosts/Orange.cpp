#include "Orange.h"

Orange::Orange(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
	this->mqttClient = &mqttClient;
	this->gameModel = &gameModel;
	this->player = &player;
	robotId = std::string("robot5");

	dispersionTile = {0, 30}; // TODO: ver MAZE_HEIGHT
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

	isMoving = false;
	setSetpoint(getSetpoint({16, 17}));
	objectiveTile = {16, 17};
}

void Orange::update(float deltaTime)
{
	if ((gameModel->getRemainingDots() <= 205) && (gameModel->getGameTime() > 0)) // tiene que empezar cuando el jugador haya comido 30 dots
	{
		ghostState(deltaTime);
	}
}

void Orange::calculateObjectiveTile() // TODO
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