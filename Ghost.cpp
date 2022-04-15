#include "Ghost.h"
#include "GameModel.h"

void Ghost::calculateNewDirection()
{
    float distanceObjectiveTile[4] = {0.0f, 0.0f, 0.0f, 0.0f};     // 0 (UP), 1 (RIGHT), 2 (DOWN) ,3 (LEFT)
    
    const float maxDistance = 50.0f;
    float minDistance = maxDistance;

    for (int i = 0; i < 4; i++)
    {
        if (i != lastDirection)
        {
            Vector2 nextTile = getTilePosition(setpoint);
            switch (i)
            {
                case 0: //Going Up
                    nextTile = Vector2Subtract(nextTile, { 0,1 });
                    break;
                case 1: //Going Right
                    nextTile = Vector2Add(nextTile, { 1,0 });
                    break;
                case 2: //Going Down
                    nextTile = Vector2Add(nextTile, { 0,1 });
                    break;
                case 3: //Going Left
                    nextTile = Vector2Subtract(nextTile, { 1,0 });
                    break;
            }

            if (gameModel->isTileFree(nextTile))
            {
                distanceObjectiveTile[i] = Vector2Length(Vector2Subtract(objectiveTile, nextTile));
                
                if (distanceObjectiveTile[i] < minDistance)
                {
                    minDistance = distanceObjectiveTile[i];
                    newDirection = i;
                }
            }
        }
    }

    lastDirection = newDirection;
}

void Ghost::move(float deltaTime)
{
    const float position = 0.60 * deltaTime;
    Setpoint robotFutureLocation = setpoint;
    
    switch(newDirection)
    {
        case 0:
            setpoint = moveUp(position, robotFutureLocation);
            break;
        case 1:
            setpoint = moveRight(position, robotFutureLocation);
            break;
        case 2:
            setpoint = moveDown(position, robotFutureLocation);
            break;
        case 3:
            setpoint = moveLeft(position, robotFutureLocation);
            break;
    }

    setSetpoint(setpoint);
}