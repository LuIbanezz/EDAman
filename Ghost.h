#ifndef _GHOST_H
#define _GHOST_H

#include "Robot.h"
#include "raymath.h"
#include "Player.h"

class Ghost : public Robot
{
public:
    virtual void start() = 0;
    virtual void update(float deltaTime) = 0;

protected:
    Vector2 objectiveTile;
    Vector2 dispersionTile;
    int lastDirection;
    int newDirection;

    virtual void calculateObjectiveTile() = 0;  // TODO in red, pink, cyan, orange
    void calculateNewDirection();       // TODO
    void move(float deltaTime);           // TODO
    void exitCage();
};

#endif  // _GHOST_H