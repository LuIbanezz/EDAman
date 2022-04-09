#include "Player.h"

Player::Player(MQTTClient& mqttClient, GameModel& gameModel)
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
	// TODO: Ver si lo que le mandamos al display va en start o en el constructor
	setDisplay(0);
	setEyes(YELLOW, YELLOW);
	//liftTo(0, -9);
    robotLocation = { 0.0,1.0,ROTATION_DOWN };

}

void Player::update(float deltaTime)
{
	//vel que queremos m/s (fija(dato)) * 100 cm/m * deltaTime 
	//0.64 * 100 * delta time ===>sumamos en la coordenada X o Y
	//0.72 """"""
    
    if(isNextLocationPosible(deltaTime))
    {
		if (lastKeyPressed == KEY_UP)
		{
            setSetpoint(robotLocation);
		}
		else if (lastKeyPressed == KEY_RIGHT)
		{
            setSetpoint(robotLocation);
		}
		else if (lastKeyPressed == KEY_LEFT)
		{
            setSetpoint(robotLocation);
		}
		else if (lastKeyPressed == KEY_DOWN)
		{
            setSetpoint(robotLocation);
		}
    }
}

void Player::setKeyboardKey(KeyboardKey lastKeyPressed)
{
	this->lastKeyPressed = lastKeyPressed;
}

bool Player::isNextLocationPosible(float deltaTime)
{
    RobotSetpoint robotFutureLocation = robotLocation;

    if (lastKeyPressed == KEY_UP)
    {
        robotFutureLocation.positionZ += 0.064 * deltaTime;
        robotFutureLocation.rotation = ROTATION_UP;
    }
    else if (lastKeyPressed == KEY_RIGHT)
    {
        robotFutureLocation.positionX += 0.064 * deltaTime;
        robotFutureLocation.rotation = ROTATION_RIGHT;
    }
    else if (lastKeyPressed == KEY_LEFT)
    {
        robotFutureLocation.positionX -= 0.064 * deltaTime;
        robotFutureLocation.rotation = ROTATION_LEFT;
    }
    else if (lastKeyPressed == KEY_DOWN)
    {
        robotFutureLocation.positionZ -= 0.064 * deltaTime;
        robotFutureLocation.rotation = ROTATION_DOWN;
    }
    
    if (gameModel->isTileFree(getMazePosition(robotFutureLocation)))
    {
        robotLocation = robotFutureLocation;
        return true;
    }

    return false;
}