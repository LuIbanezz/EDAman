#ifndef _CYAN_H
#define _CYAN_H

#include "../Ghost.h"
#include "Red.h"

class Cyan : public Ghost
{
public:
	Cyan(MQTTClient &mqttClient, GameModel &gameModel, Player &player, Red &red);
	~Cyan();

	void start();
	void update(float deltaTime);

private:
	Player *player;
	Red* red;
	void calculateObjectiveTile();
};

#endif // _CYAN_H