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

    // TODO: Ver si lo que le mandamos al display va en start o en el constructor
    setDisplay(0);
    setEyes(YELLOW,YELLOW);
}

void Player::update(float deltaTime)
{
    //vel que queremos m/s (fija(dato)) * 100 cm/m * deltaTime 
    //0.64 * 100 * delta time ===>sumamos en la coordenada X o Y
    //0.72 """"""
    if (lastKeyPressed == KEY_UP && gameModel->isTileFree(getMazePosition(robotLocation)))
    {
        robotLocation.positionZ += 0.64 * 100 * deltaTime;
        setSetpoint(robotLocation);
    }
    else if (lastKeyPressed == KEY_RIGHT && gameModel->isTileFree(getMazePosition(robotLocation)))
    {
        robotLocation.positionX += 0.64 * 100 * deltaTime;
        setSetpoint(robotLocation);
    }
    else if (lastKeyPressed == KEY_LEFT && gameModel->isTileFree(getMazePosition(robotLocation)))
    {
        robotLocation.positionX -= 0.64 * 100 * deltaTime;
        setSetpoint(robotLocation);
    }
    else if (lastKeyPressed == KEY_DOWN && gameModel->isTileFree(getMazePosition(robotLocation)))
    {
        robotLocation.positionZ -= 0.64 * 100 * deltaTime;
        setSetpoint(robotLocation);
    }
}

void Player::setKeyboardKey(KeyboardKey lastKeyPressed) {
    this->lastKeyPressed = lastKeyPressed;
}