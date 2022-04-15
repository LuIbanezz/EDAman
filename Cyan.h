#ifndef _CYAN_H
#define _CYAN_H

#include "Ghost.h"

class Cyan : public Ghost
{
public:
	Cyan(MQTTClient &mqttClient, GameModel &gameModel, Player &player);
	~Cyan();

	void start();
	void update(float deltaTime);

private:
	Player *player;
	void calculateObjectiveTile();
};

#endif // _CYAN_H