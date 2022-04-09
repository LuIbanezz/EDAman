/**
 * Robot base class.
 *
 * Copyright (C) 2022 Marc S. Ressl
 */

#ifndef _ROBOT_H
#define _ROBOT_H

#define ROTATION_LEFT 270
#define ROTATION_UP 0
#define ROTATION_RIGHT 90
#define ROTATION_DOWN 180

class GameModel;

struct RobotSetpoint
{
    RobotSetpoint(float positionX = 0, float positionZ = 0, float rotation = 0)
    {
        this->positionX = positionX;
        this->positionZ = positionZ;
        this->rotation = rotation;
    }

    float positionX;
    float positionZ;
    float rotation;
};

#include <iostream>
#include <string>
#include <vector>

#include <raylib.h>

#include "MQTTClient.h"
#include "GameModel.h"

class Robot
{
public:
    Robot();
    virtual ~Robot();

    virtual void start() = 0;
    virtual void update(float deltaTime);

protected:
    // NOTE: These variables should be set by your child class:
    MQTTClient *mqttClient;
    GameModel *gameModel;
    std::string robotId;

    RobotSetpoint robotLocation;

    Image displayImages;

    MazePosition getMazePosition(RobotSetpoint setpoint);
    RobotSetpoint getRobotSetpoint(MazePosition mazePosition, float rotation);
    void setSetpoint(RobotSetpoint setpoint);
    void liftTo(float positionX, float positionZ);
    void setDisplay(int imageIndex);
    void setEyes(Color leftEye, Color rightEye);
};

#endif
