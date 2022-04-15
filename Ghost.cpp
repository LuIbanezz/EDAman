#include "Ghost.h"
#include "GameModel.h"

void Ghost::calculateNewDirection(GameModel &gameModel)
{
    float distanceObjectiveTile[4] = {0.0f, 0.0f, 0.0f, 0.0f};     // 0 (UP), 1 (RIGHT), 2 (DOWN) ,3 (LEFT)
    
    const float maxDistance = 50.0f;
    float minDistance = maxDistance;

    for (int i = 0; i < 4; i++)
    {
        if (i != lastDirection)
        {
            Vector2 nextTile = getTilePosition(currentPosition);
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

            if (gameModel.isTileFree(nextTile))
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
}

void Ghost::move(int direction)
{
    switch(direction)
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
}