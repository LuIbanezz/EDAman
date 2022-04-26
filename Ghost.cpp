#include "Ghost.h"
#include "Game/GameModel.h"
#include <cstring>

Ghost::Ghost()
{
    srand(time(NULL));

}

void Ghost::calculateNewDirection()
{
    float distanceObjectiveTile[4] = {0.0f, 0.0f, 0.0f, 0.0f}; // 0 (UP), 1 (RIGHT), 2 (DOWN) ,3 (LEFT)

    const float maxDistance = 50.0f;
    float minDistance = maxDistance;

    for (int i = 0; i < 4; i++)
    {
        if (i != (lastDirection + 2) % 4)
        {
            Vector2 nextTile = getTilePosition(setpoint);
            switch (i)
            {
            case 0: // Going Up
                nextTile = Vector2Subtract(nextTile, {0, 1});
                break;
            case 1: // Going Right
                nextTile = Vector2Add(nextTile, {1, 0});
                break;
            case 2: // Going Down
                nextTile = Vector2Add(nextTile, {0, 1});
                break;
            case 3: // Going Left
                nextTile = Vector2Subtract(nextTile, {1, 0});
                break;
            }
            
            if (gameModel->isTileFree(nextTile))
            {
                distanceObjectiveTile[i] = Vector2Length(Vector2Subtract(objectiveTile, 
                                                                            nextTile));

                if (minDistance - distanceObjectiveTile[i] > 0.25)    // dejo margen de error, si las 
                {                                                     // distancias son muy parecidas, 
                    minDistance = distanceObjectiveTile[i];           // gasto menos energia si sigo de largo que si giro.
                    newDirection = i;
                }
            }
        }
    }

    lastDirection = newDirection;
}

void Ghost::calculateBlueObjectiveTile()
{
    int direction;
    
    do {
        direction = rand() % 4;
    } while (direction != lastDirection);

    switch (direction)
    {
        case 0:
            objectiveTile = Vector2Subtract(getTilePosition(setpoint), { 0,1 });
            break;
        case 1:
            objectiveTile = Vector2Add(getTilePosition(setpoint), {1, 0});
            break;
        case 2:
            objectiveTile = Vector2Add(getTilePosition(setpoint), { 0, 1 });
            break;
        case 3:
            objectiveTile = Vector2Subtract(getTilePosition(setpoint), { 1,0 });
            break;
    }

}

void Ghost::move(float deltaTime)
{
    float velocity;
    if (dead)
    {
        velocity = 0.7;
    }
	else if (gameModel->getGameState() == Blue)
	{
    	velocity = 0.4;
    }
	else
    {
		velocity = 0.55;
    }
	const float position = velocity * deltaTime;

    switch (newDirection)
    {
        case 0:
            setpoint = moveUp(position, setpoint);
            break;
        case 1:
            setpoint = moveRight(position, setpoint);
            break;
        case 2:
            setpoint = moveDown(position, setpoint);
            break;
        case 3:
            setpoint = moveLeft(position, setpoint);
            break;
    }
    setSetpoint(setpoint);
}

void Ghost::exitCage()
{
    setpoint = getSetpoint({14, 15});
    setSetpoint(setpoint);
    isMoving = true;
    lastDirection = 0;
}

//SETTERS
void Ghost::setObjectiveTile(Vector2 tilePosition)
{
    objectiveTile = tilePosition;
}

void Ghost::ghostState(float deltaTime)
{
    if (!isMoving || (((GetTime() - deadTimer) > 4) && dead))
    {
        setDisplay(16 + 2 * (robotId[5] - '0' - 2));
        exitCage();
        dead = false;
    }
    else if (!dead)
    {
        switch (gameModel->getGameState())
        {
        case(Persecution):
            calculateObjectiveTile();
            break;
        case(Dispersion):
            objectiveTile = dispersionTile;
            break;
        case(Blue):
            calculateBlueObjectiveTile();
            break;
        }

        calculateNewDirection();
        move(deltaTime);
    }
}

