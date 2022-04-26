#include "Pink.h"

Pink::Pink(MQTTClient &mqttClient, GameModel &gameModel, Player &player)
{
	this->mqttClient = &mqttClient;
	this->gameModel = &gameModel;
	this->player = &player;
	robotId = std::string("robot3");

	dispersionTile = {2, -2};
}

Pink::~Pink()
{
	mqttClient->disconnect();
}

void Pink::start()
{
	setDisplay(19);
	setEyes(PINK, PINK);

	liftTo({0, 0, 0});
	setpoint.rotation = ROTATION_UP;
	setSetpoint(getSetpoint({14, 17}));
	objectiveTile = {14, 17};

	isMoving = false;
}

void Pink::update(float deltaTime)
{
	if (gameModel->getGameTime() > 0) // pink tambien est� libre al inicio
	{
		ghostState(deltaTime);
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