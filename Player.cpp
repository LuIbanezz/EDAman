#include "Player.h"

Player::Player(MQTTClient& mqttClient, GameModel& gameModel)
{
	this->mqttClient = &mqttClient;
	this->gameModel = &gameModel;
	robotId = std::string("robot1");
	lastKeyPressed = KEY_NULL;
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
	liftTo(0, -0.8);
	robotLocation = getRobotSetpoint({ 14,26 }, ROTATION_DOWN);
	setSetpoint(robotLocation);

}

void Player::update(float deltaTime)
{
	//vel que queremos m/s (fija(dato)) * 100 cm/m * deltaTime 
	//0.64 * 100 * delta time ===>sumamos en la coordenada X o Y
	//0.72 """"""

	if (isNextLocationPosible(deltaTime))
	{
		setSetpoint(robotLocation);

	}
}

void Player::setKeyboardKey(KeyboardKey lastKeyPressed)
{
	this->lastKeyPressed = lastKeyPressed;
}

bool Player::isNextLocationPosible(float deltaTime)
{
	RobotSetpoint robotFutureLocation = robotLocation;
	//robotFutureLocation.positionZ += 0.009;
	//robotFutureLocation.positionX += 0.009;

	if (lastKeyPressed == KEY_UP)
	{
		robotFutureLocation.positionZ += 1.088 * deltaTime;
		robotFutureLocation.rotation = ROTATION_UP;
	}
	else if (lastKeyPressed == KEY_RIGHT)
	{
		robotFutureLocation.positionX += 1.088 * deltaTime;
		robotFutureLocation.rotation = ROTATION_RIGHT;
	}
	else if (lastKeyPressed == KEY_LEFT)
	{
		robotFutureLocation.positionX -= 1.088 * deltaTime;
		robotFutureLocation.rotation = ROTATION_LEFT;
	}
	else if (lastKeyPressed == KEY_DOWN)
	{
		robotFutureLocation.positionZ -= 1.088 * deltaTime;
		robotFutureLocation.rotation = ROTATION_DOWN;
	}

	if (gameModel->isTileFree(getMazePosition(robotFutureLocation)))
	{
		robotLocation = robotFutureLocation;
		return true;
	}

	return false;
}