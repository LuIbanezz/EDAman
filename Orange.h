#ifndef _ORANGE_H
#define _ORANGE_H

#include "Ghost.h"

class Orange : public Ghost
{
public:
	Orange(MQTTClient &mqttClient, GameModel &gameModel, Player &player);
	~Orange();

	void start();
	void update(float deltaTime);

private:
	Player *player;
	void calculateObjectiveTile();
};

#endif // _ORANGE_H