/**
 * Robot base class.
 *
 * @copyright Copyright (C) 2022
 * @author Marc S. Ressl
 */

#ifndef _ROBOT_H
#define _ROBOT_H

#define ROTATION_UP 0
#define ROTATION_RIGHT 90
#define ROTATION_DOWN 180
#define ROTATION_LEFT 270

class GameModel;

#include <iostream> //testeo
#include <string>
#include <vector>

#include <raylib.h>

#include "MQTTClient.h"
#include "Game/GameModel.h"

/**
 * @brief Robot controller setpoint.
 * 
 * position.x is world position x
 * position.y is world position z
 * rotation is world rotation y
 */
struct Setpoint
{
    Vector2 position;
    float rotation;
};

/**
 * @brief Indicates a robot direction.
 * 
 */
enum Direction
{
    DirectionNone,
    DirectionUp,
    DirectionRight,
    DirectionDown,
    DirectionLeft
};

class Robot
{
public:
    Robot();
    virtual ~Robot();

    virtual void start()=0;
    virtual void update(float deltaTime)=0;

protected:
    // These variables should be set by you...
    MQTTClient *mqttClient;
    GameModel *gameModel;
    std::string robotId;

    Image displayImages;

    bool isMoving;
    Setpoint setpoint;

    // Add your variables here...
    Setpoint moveUp (float position, Setpoint futurePosition);
    Setpoint moveDown (float position, Setpoint futurePosition);
    Setpoint moveLeft (float position, Setpoint futurePosition);
    Setpoint moveRight (float position, Setpoint futurePosition);

    Vector2 getTilePosition(Setpoint setpoint);
    Setpoint getSetpoint(Vector2 tilePosition);
    void setSetpoint(Setpoint setpoint);
    void liftTo(Vector3 destination); //TO DO revisar parametro vector3
    void setDisplay(int imageIndex);
    void setEyes(Color leftEye, Color rightEye);
};

#endif
