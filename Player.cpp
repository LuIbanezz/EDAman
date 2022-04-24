#include <raylib.h>
#include "raymath.h"
#include "Player.h"

Player::Player(MQTTClient &mqttClient, GameModel &gameModel)
{
	this->mqttClient = &mqttClient;
	this->gameModel = &gameModel;
	robotId = std::string("robot1");
	lastKeyPressed = KEY_NULL;
	previousDirection = KEY_NULL;
}

Player::~Player()
{
	mqttClient->disconnect();
}

void Player::start()
{
	// TODO: Ver si lo que le mandamos al display va en start o en el constructor
	setDisplay(1);
	setEyes(YELLOW, YELLOW);
	setpoint.rotation = ROTATION_DOWN;
	setpoint = getSetpoint({13, 26});
	setSetpoint(setpoint);
}

void Player::update(float deltaTime)
{
	if ((lastKeyPressed != KEY_NULL) && (gameModel->getGameTime() == 0))
	{
		gameModel->setGameTime(GetTime());
	}

	if (check(deltaTime, true))
	{
		setSetpoint(setpoint);
	}
	else if (check(deltaTime, false))
	{
		setSetpoint(setpoint);
	}
}

void Player::setKeyboardKey(KeyboardKey lastKeyPressed)
{
	this->lastKeyPressed = lastKeyPressed;
}

Vector2 Player::getPlayerPosition()
{
	return getTilePosition(setpoint);
}

bool Player::check(float deltaTime, bool nextMove)
{
	KeyboardKey option;
	const float position = 0.64 * deltaTime;
	Setpoint robotFutureLocation = setpoint;

	// robotFutureLocation.position = 0.009 * deltaTime;
	// robotFutureLocation.positionX += 0.009;

	if (nextMove)
	{
		option = lastKeyPressed;
	}
	else
	{
		option = previousDirection;
	}

	if (option == KEY_UP)
	{
		robotFutureLocation = moveUp(position, robotFutureLocation);
	}
	else if (option == KEY_RIGHT)
	{
		robotFutureLocation = moveRight(position, robotFutureLocation);
	}
	else if (option == KEY_LEFT)
	{
		robotFutureLocation = moveLeft(position, robotFutureLocation);
	}
	else if (option == KEY_DOWN)
	{
		robotFutureLocation = moveDown(position, robotFutureLocation);
	}

	if (gameModel->isTileFree(getTilePosition(robotFutureLocation)))
	{
		setpoint = robotFutureLocation;
		if (nextMove)
		{
			previousDirection = lastKeyPressed;
		}
		return true;
	}

	return false;
}

void Player::eatDots()
{
	gameModel->eat(getTilePosition(setpoint));
}