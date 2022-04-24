#include <raylib.h>
#include "raymath.h"
#include "Player.h"

Player::Player(MQTTClient &mqttClient, GameModel &gameModel)
{
	this->mqttClient = &mqttClient;
	this->gameModel = &gameModel;
	robotId = std::string("robot1");
	lastKeyPressed = KEY_NULL;
	lastDirection = KEY_NULL;
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

int Player::getPlayerDirection()
{
	int direction = 0; 

	switch (lastDirection)
    {
        case (KEY_UP):
            direction = 0;
            break;
        case (KEY_RIGHT):
            direction = 1;
            break;
        case (KEY_DOWN):
            direction = 2;
            break;
        case (KEY_LEFT):
            direction = 3;
            break;
    }

	return direction;
}

bool Player::check(float deltaTime, bool nextMove)
{
	KeyboardKey option;
	const float position = 0.64 * deltaTime;
	Setpoint robotFutureLocation = setpoint;

	if (nextMove)
	{
		option = lastKeyPressed;
	}
	else
	{
		option = lastDirection;
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
			lastDirection = lastKeyPressed;
		}
		return true;
	}

	return false;
}

void Player::eatDots()
{
	gameModel->eat(getTilePosition(setpoint));
}