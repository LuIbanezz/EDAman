#ifndef _PINK_H_
#define _PINK_H_

#include "Ghost.h"

class Pink : public Ghost
{
public:
	Pink(MQTTClient& mqttClient, GameModel& gameModel, Player &player);
	~Pink();

	void start();
	void update(float deltaTime);

private:
	Player *player;
	void calculateObjectiveTile();
};

#endif // _PINK_H_