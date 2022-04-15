#include <raylib.h>
#include "raymath.h"
#include "Player.h"


Player::Player(MQTTClient& mqttClient, GameModel& gameModel)
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
	liftTo({ 0.0, 0.0, -0.8 });
	setpoint.rotation = ROTATION_DOWN;
	setpoint = getSetpoint({ 14,26 });
	setSetpoint(setpoint);
}

void Player::update(float deltaTime)
{
	//vel que queremos m/s (fija(dato)) * 100 cm/m * deltaTimet
	//0.64 * 100 * delta time ===>sumamos en la coordenada X o Y
	//0.72 """"""

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

bool Player::check(float deltaTime, bool nextMove)
{
	KeyboardKey option;
	const float position = 0.64 * deltaTime;
	Setpoint robotFutureLocation = setpoint;

	//robotFutureLocation.position = 0.009 * deltaTime;
	//robotFutureLocation.positionX += 0.009;

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

Vector2 Player::getPlayerPosition()
{
	return getTilePosition(setpoint);
}