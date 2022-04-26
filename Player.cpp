#include <raylib.h>
#include "raymath.h"
#include "Player.h"

Player::Player(MQTTClient &mqttClient, GameModel &gameModel)
{
	this->mqttClient = &mqttClient;
	this->gameModel = &gameModel;
	robotId = std::string("robot1");
}

Player::~Player()
{
	mqttClient->disconnect();
}

void Player::start()
{
	setDisplay(1);
	setEyes(YELLOW, YELLOW);

	setpoint.rotation = ROTATION_DOWN;
	setSetpoint(getSetpoint({14, 26}));

	lastKeyPressed = KEY_NULL;
	lastDirection = KEY_NULL;
	dead = false;
}

void Player::update(float deltaTime)
{
	if ((lastKeyPressed != KEY_NULL) && (gameModel->getGameTime() == 0)) //esto es para que arranque el tiempo cuando se presiona la primer tecla
	{
		gameModel->setGameTime(GetTime());
		gameModel->setViewMessage(0);		// GameViewMessageNone = 0
	}

	if (check(deltaTime, true))
	{
		setSetpoint(setpoint);
	}
	else if (check(deltaTime, false))
	{
		setSetpoint(setpoint);
	}
	eatDots();
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
	Setpoint robotFutureLocation = setpoint;

	float velocity;
	if (gameModel->getGameState() == Blue)
		velocity = 0.7;
	else
		velocity = 0.64;
	const float position = velocity * deltaTime;

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

	// TODO: if (gameModel->isTileFree({robotFutureLocation.position.x,robotFutureLocation}))
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