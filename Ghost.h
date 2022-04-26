#ifndef _GHOST_H
#define _GHOST_H

#include "Robot.h"
#include "raymath.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

class Ghost : public Robot
{
public:
    Ghost();

    virtual void start() = 0;
    virtual void update(float deltaTime) = 0;

    void setObjectiveTile(Vector2 tilePosition);

protected:
    Vector2 objectiveTile;
    Vector2 dispersionTile;
    int lastDirection;
    int newDirection;

    void ghostState(float deltaTime);
    virtual void calculateObjectiveTile() = 0;
    void calculateBlueObjectiveTile();
    void calculateNewDirection();
    void move(float deltaTime);
    void exitCage();
};

#endif // _GHOST_H